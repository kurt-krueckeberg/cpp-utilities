#ifndef line_h
#define line_h
#include <string>
#include <memory>

/*
This std::string wrapper class that allows std::string to be used with std::istream_iterator?
*/
struct Line {

    std::string lineData;
    
   /*
    * This conversion operator converts Line to an lvalue of type 'const std::string&', enabling it to be used with algorithms
    * that take an lvalue like 'std::copy()'.
    */
       
    operator const std::string&() const // for use with std::copy, etc.
    {
       return lineData;
    }
   /*
    * This conversion operator converts Line to the rvalue 'std::string&&', enabling Line to be seemless used with algorithms taking
    * an rvalue like std::move().
    */
    operator std::string&&() 
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
