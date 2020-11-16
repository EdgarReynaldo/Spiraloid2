


#include "Spirals.hpp"
#include "Display.hpp"



#include "Program.hpp"



#include <cstdio>



int main(int argc , char** argv) {
   
   (void)argc;
   (void)argv;

   Program proggie;
   
   if (proggie.InitState() != 0) {
      return proggie.InitState();
   }

   proggie.Run();
   
   return 0;
}

