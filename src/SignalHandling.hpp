

#ifndef SignalHandling_HPP
#define SignalHandling_HPP

#include <cstdio>
#include <stdexcept>
#include <string>
using std::string;


void Assert(bool exp);

class Exception : public std::runtime_error {
   
public :
   string s;
   Exception(string error) :
         runtime_error(error.c_str()),
         s(error)
   {
      printf("%s\n" , s.c_str());
      Assert(0);
   }
   Exception(const char* error) :
         runtime_error(error),
         s(error)
   {
      printf("%s\n" , s.c_str());
      Assert(0);
   }
   
   ~Exception() throw() {}
   
   const char* what() {return s.c_str();}
};


#endif // SignalHandling_HPP

