// See:
// https://stackoverflow.com/a/1567703/33758 

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>

class line {
    std::string data;
public:
    friend std::istream &operator>>(std::istream &is, line &l) {
        std::getline(is, l.data);
        return is;
    }
    operator std::string() const { return data; }    
};

std::vector<std::string> read_input(std::istream& ifs)
{
    std::vector<std::string> lines;
    std::copy(std::istream_iterator<line>(ifs), 
            std::istream_iterator<line>(),
            std::back_inserter(lines));
    return lines;
}

std::vector<std::string> read_input(const std::string& f)
{
    auto ifs = std::ifstream(f,std::ifstream::in);
    if (!ifs) {
        std::cerr << "Unable to open file: " << f << "\n";
        exit(-1);
    }
    return read_input(ifs);
}
