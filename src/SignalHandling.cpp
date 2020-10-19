
#include <cstdio>
#include "Eagle.hpp"


void AllegroAssertHandler(const char* exp , const char* file , int line , const char* func) {
   printf("assert(%s) failed in file %s on line %d in function %s.\n" , exp , file , line , func);
   EAGLE_ASSERT(false);
}


