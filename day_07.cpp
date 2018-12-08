// Advent of Code 2018
// Day 07 - 

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

set<char> available(set<char> chars, multimap<char,char> has_dep)
{
    for (auto dep:has_dep) {
        cout << dep.first << " has dep of " << dep.second << "\n";
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

// set<char> recurse_deps(char c,map<char,char> has_dep)
// {
//     set<char> deps;


// }

// map<char,char> get_transitive_deps(set<char> chars,map<char,char> has_dep)
// {
//     // add in transitive deps
//     for (auto c:chars) {
//         auto deps = recurse_deps(c,has_dep);
//         for (auto cd:deps) {
//             has_dep.push_back(make_pair(c,cd));
//         }
//     }
//     return has_dep;
// }

// int main()
// {
//     auto chars = set<char>{};
//     auto has_dep = multimap<char,char>{};

//     // Step T must be finished before step W can begin.
//     // read data
//     FILE *f = fopen(FILENAME,"rb");
//     char fs,ss;
//     while (!feof(f) && fscanf(f,"Step %c must be finished before step %c can begin.\n",&fs,&ss)) {
//         printf("%c -> %c\n",fs,ss);
//         chars.insert(fs);
//         chars.insert(ss);
//         has_dep.insert(make_pair(ss,fs));
//     }
//     fclose(f);

//     // transitive deps
// //    has_dep = get_transitive_deps(chars,has_dep);

//     auto order = string{""};

//     // for each step,
//     while (chars.size()>0) {
//         // candidates w/ no dependencies
//         auto candidates = available(chars,has_dep);

//         // do first only
//         auto c = *(begin(candidates));
//         order.push_back(c);

//         // clean up dependencies
//         has_dep = done_step(c, has_dep);
//         chars.erase(c);

//         // print order so far
//         cout << order << "\n";
//     }

//     printf("Part 1: ...: \n");

//     printf("Part 2: ...: \n");
//     return 0;
// }


// work_queue
// initialize with a count of workers, at time 0
// call assign to assign a job to complete
// 
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
        cout << "tick\n";
        assert(haswork());
        std::stable_sort(begin(tasks),end(tasks),[&](const auto& l,const auto& r){return l.second<r.second;});
        return (thetime=tasks.front().second);
    };

    vector<pair<char,int>> completed()
    {
        cout << "completed()\n";
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

    pair<char,int> work(char c) {        // assign and return task,eta for this job
        cout << "Work: " << c << " " << thetime+TIME+c-'A' << "\n";
        assert(!busy());                // must have at least one elf free
        auto t = make_pair(c,thetime+/* 61 or 1 */TIME+c-'A');
        tasks.push_back(t);
        return t;
    };
private:
    vector<pair<char,int>> tasks;
    int workers;
    int thetime;
};


// part 2
int main()
{
    auto chars = set<char>{};
    auto has_dep = multimap<char,char>{};

    // Step T must be finished before step W can begin.
    // read data
    FILE *f = fopen(FILENAME,"rb");
    char fs,ss;
    while (!feof(f) && fscanf(f,"Step %c must be finished before step %c can begin.\n",&fs,&ss)) {
        printf("%c -> %c\n",fs,ss);
        chars.insert(fs);
        chars.insert(ss);
        has_dep.insert(make_pair(ss,fs));
    }
    fclose(f);

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

            // job order
            auto done = w.completed();
            for (auto completed : done) {
                cout << "Completed: " << completed.first << " at time: " << completed.second << "\n";

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

