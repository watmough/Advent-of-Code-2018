// Advent of Code 2018
// Day 07 - The Sum of Its Parts

#include "aoc.hpp"
using namespace std;

#if 1
    #define FILENAME "day_07.txt"
    #define COUNT 101
    #define WORKERS 5
    #define TIME 61
#else
    #define FILENAME "day_07_tst.txt"
    #define COUNT 7
    #define WORKERS 2
    #define TIME 1
#endif

void load_input(set<char>& chars, multimap<char,char>& has_dep)
{
    // Sample data: Step T must be finished before step W can begin.
    FILE *f = fopen(FILENAME,"rb");
    char fs,ss;
    while (!feof(f) && fscanf(f,"Step %c must be finished before step %c can begin.\n",&fs,&ss)) {
        // printf("%c -> %c\n",fs,ss);
        chars.insert(fs);
        chars.insert(ss);
        has_dep.insert(make_pair(ss,fs));
    }
    fclose(f);
}

set<char> available(set<char> chars, multimap<char,char> has_dep)
{
    for (auto dep : has_dep) {
        // cout << dep.first << " has dep of " << dep.second << "\n";
        chars.erase(dep.first);
    }
    return chars;
}

multimap<char,char> done_step(char c, multimap<char,char> has_dep)
{
    multimap<char,char> new_deps;
    for (auto d : has_dep) {
        if (d.second!=c)
            new_deps.insert(d);
    }
    return new_deps;
}

// Part 1 - Calculate the required ordering of the steps given the constraints
void part1()
{
    auto chars = set<char>{};
    auto has_dep = multimap<char,char>{};
    load_input(chars,has_dep);

    auto order = string{""};
    while (chars.size()>0) {
        // candidates w/ no dependencies
        auto candidates = available(chars,has_dep);

        // do first only
        auto c = *(begin(candidates));
        order.push_back(c);

        // done a task, make more tasks available
        has_dep = done_step(c, has_dep);
        chars.erase(c);
    }

    cout << "Part 1: The required task ordering is: " << order << "\n";
}

// Simulate a work queue ... of Elves
class work_queue
{
public:
    work_queue(int workers) : tasks(), workers(workers), thetime{0} {};

    bool inflight(char c) {
        return any_of(begin(tasks),end(tasks),[&](const auto& t)->bool{return t.first==c;});
    }

    int gettime() {
        return thetime;
    };

    int tick() {    // tick to the soonest available job, returning the time (may be >1 job)
        assert(haswork());
        std::stable_sort(begin(tasks),end(tasks),[&](const auto& l,const auto& r){return l.second<r.second;});
        return (thetime=tasks.front().second);
    };

    vector<pair<char,int>> completed()
    {
        auto done = vector<pair<char,int>>{};
        copy_if(begin(tasks),end(tasks),std::back_inserter(done),[&](const auto& t)->bool{return t.second==thetime;});
        for_each(begin(done),end(done),[&](const auto& t){tasks.erase(tasks.begin());});
        return done;
    }

    bool haswork() {
        return !tasks.empty();
    }

    bool busy() {
        return tasks.size()==workers;
    };

    pair<char,int> work(char c) {           // assign and return task,eta for this job
        assert(!busy());                    // must have at least one elf free
        auto t = make_pair(c,thetime+/* 61 or 1 */TIME+c-'A');
        tasks.push_back(t);
        return t;
    };
private:
    vector<pair<char,int>> tasks;
    int workers;
    int thetime;
};

int part2()
{
    auto chars = set<char>{};
    auto has_dep = multimap<char,char>{};
    load_input(chars,has_dep);

    // create a work queue
    work_queue w(WORKERS);

    // get candidates for next worker
    auto candidates = available(chars,has_dep);

    // for each step,
    while (chars.size()>0) {
        
        // assign a worker
        while (candidates.size() && !w.busy()) {
            auto c = *(begin(candidates)); 
            if (!w.inflight(c))
                w.work(c);
            candidates.erase(c);
        }

        // if busy, clock the next job to completion
        if (w.busy() || candidates.size()==0) {
            // clock
            w.tick();

            // handle completed tasks
            auto done = w.completed();
            for (auto completed : done) {
                // cout << "Completed: " << completed.first << " at time: " << completed.second << "\n";

                // completed a task
                has_dep = done_step(completed.first, has_dep);
                chars.erase(completed.first);

                // refresh list of candidates 
                // ### No Clang warning for having an auto on the next line ###
                candidates = available(chars,has_dep);
            }
        }
    }
    printf("Part 2: Finished at time: %d\n",w.gettime());
    return 0;
}

int main()
{
    part1();
    part2();
    return 0;
}
