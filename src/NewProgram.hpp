



#ifndef NewProgram_HPP
#define NewProgram_HPP


class Allegro5System;
class EagleGraphicsContext;

#include "Eagle/Config.hpp"

#include "NewDisplay.hpp"
#include "Monitors.hpp"
#include "Eagle/ConfigFile.hpp"

void AllegroLogHandler(const char* text);
void AllegroLogHandler(const char* text) {
   EagleInfo() << text << std::endl;
}


class NewProgram {
   
   Allegro5System* sys;
   EagleGraphicsContext* win;
   
   GraphicsConfig config;
   MonitorInfo minfo;
   NewDisplay display;
   

   #define NUM_SCREENS 1
   SpiraloidScreen spiraloid_screen;
   
   ProgramScreen* screens[NUM_SCREENS];
   int active_screen;
   
   bool fullscreen;
   bool redraw;
   bool quit;

public :
   
   NewProgram();
   bool Init();
   
};

#endif // NewProgram_HPP
