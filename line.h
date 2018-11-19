#ifndef line_h
#define line_h
#include <string>
#include <memory>

struct Line {

    std::string lineData;
   
    operator const std::string&() const // for use with std::copy, etc.
    {
       return lineData;
    }
    
    operator std::string&&() // for use with std::move() algorithm
    {
       return std::move(lineData);
    }
      
    friend std::istream& operator>>(std::istream& istr, Line& line)
    {
        getline(istr, line.lineData);
        return istr;
    }
    
    friend std::ostream& operator<<(std::ostream& ostr, const Line& line)
    {
        return ostr << line.lineData; 
    }
};
#endif
