




#ifndef Program_HPP
#define Program_HPP



#include "Eagle/backends/Allegro5Backend.hpp"
#include "Eagle.hpp"



#include "Monitors.hpp"
#include "Display.hpp"
#include "SpiraloidController.hpp"
#include "SpiraloidScreen.hpp"



class Program {
   
private :
   Allegro5System* a5sys;
//   EagleGraphicsContext* win;
   EagleTimer* timer;
   EagleEventHandler* queue;
//   EagleImage* buffer;

   
   MonitorInfo monitor_info;
   
   int adapter;
   Display display;
   
   
   bool fullscreen;
   bool redraw;
   bool quit;
   
   #define NUM_SCREENS 1
   SpiraloidScreen spiraloid_screen;
   
   ProgramScreen* screens[NUM_SCREENS];
   int active_screen;
public :
   
///   Program();
   Program() :
         a5sys(GetAllegro5System()),
//         win(0),
         timer(0),
         queue(0),
//         buffer(0),
         monitor_info(),
         adapter(-1),
         display(a5sys),
         fullscreen(false),
         redraw(true),
         quit(false),
         spiraloid_screen(),
         screens(),
         active_screen(-1)
   {
      screens[0] = &spiraloid_screen;
      active_screen = 0;
   }
   
   int Init();

   void Run();
   
   
};





#endif // Program_HPP




