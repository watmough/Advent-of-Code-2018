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