


#include "NewProgram.hpp"

#include "Eagle/Logging.hpp"


int main(int argc , char** argv) {
   
   (void)argc;
   (void)argv;
   
   NewProgram proggie;
   
   bool init = proggie.Init();
   
   if (!init) {
      EagleCritical() << "Failed to initialize spiraloid program. Halting." << std::endl;
      return 1;
   }
   
   return proggie.Run();
}














