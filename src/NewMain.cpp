



#include "Eagle/Eagle/backends/Allegro5.hpp"

#include "Eagle.hpp"

#include "SpiraloidConfig.hpp"

#include <cstdlib>



int main(int argc , char** argv) {
   
   (void)argc;
   (void)argv;
   
   NewProgram proggie;
   
   bool init = proggie.Init();
   
   if (!init) {
      EagleError() << "Failed to initialize spiraloid program. Halting." << std::endl;
      return 1;
   }
   
   return proggie.Run();
}














