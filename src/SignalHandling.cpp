

#include "SignalHandling.hpp"



void Assert(bool exp) {
   if (!exp) {
      int fail = 1/0;
      (void)fail;
   }
}


