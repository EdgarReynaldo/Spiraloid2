

#include "SignalHandling.hpp"



void AllegroAssertHandler(const char* exp , const char* file , int line , const char* func) {
   printf("assert(%s) failed in file %s on line %d in function %s.\n" , exp , file , line , func);
   Assert(false);
}



void Assert(bool exp) {
   if (!exp) {
      int fail = 1/0;
      (void)fail;
   }
}


