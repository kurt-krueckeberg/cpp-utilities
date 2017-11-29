#ifndef token_iterator_h
#define token_iterator_h

#include <string>

template<char TOKEN='|'>
class token_iterator : public std::iterator<std::input_iterator_tag, std::string> {
    
  bool ok;
  
  const std::string *const str_ptr; 
    
  int  pos;
  int  prev_pos;

  const char token;
  
  void fetch_field(bool initial=false) 
  {
     ok = (str_ptr && pos != str_ptr->size()) ? true : false;

     if (!ok) prev_pos = pos; // This ensures *operator() always returns an empty string if user 
                              // calls operator++() once iteration is complete.

     if (ok) {

         if (!initial && pos != str_ptr->size()) ++pos;  // skip over token or advance to start 

         prev_pos = pos;

         pos = str_ptr->find(token, pos);

         if (pos == std::string::npos) {
             
             pos = str_ptr->size();
         }
     } 
  }

  public:

   token_iterator() : token{TOKEN}, ok{false}, str_ptr{nullptr}
   {
       prev_pos = pos = 0;
   } 

   explicit token_iterator(const std::string& in_line) : str_ptr{&in_line}, token{TOKEN}, ok{true}
   {
      prev_pos = pos = 0;
      fetch_field(true);  
   }

   token_iterator(const token_iterator& lhs) : str_ptr{lhs.str_ptr}, token{lhs.token}, pos{lhs.pos}, prev_pos{lhs.pos} {}

  ~token_iterator() {}
  
   token_iterator& operator++() 
   {
      fetch_field();
      return *this;
   }

   token_iterator operator++(int) 
   {
      token_iterator tmp{*this};

      fetch_field();

      return tmp;
   }
   
   const std::string operator*() const
   {
     auto length = (pos == std::string::npos) ? 0 : pos - prev_pos;
   
     return str_ptr->substr(prev_pos, length);
   } 

   const std::string *operator->()
   {
     return &operator*();
   }
 
   bool equal(const token_iterator& rhs) const
   {
     return (ok == rhs.ok) && (!ok || (str_ptr == rhs.str_ptr && pos == rhs.pos && prev_pos == rhs.prev_pos));
   }
};

template<char T> inline bool operator!=(const token_iterator<T>& lhs, const token_iterator<T>& rhs)
{
  return !(lhs.equal(rhs));
}

template<char T> inline bool operator==(const token_iterator<T>& lhs, const token_iterator<T>& rhs)
{
  return lhs.equal(rhs);
}
#endif
