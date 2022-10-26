




#ifndef Program_HPP
#define Program_HPP


#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_image.h"


#include "Monitors.hpp"
#include "Display.hpp"
#include "SpiraloidController.hpp"
#include "SignalHandling.hpp"
#include "SpiraloidScreen.hpp"



class Program {
   
private :
   
   MonitorInfo monitor_info;
   
   int adapter;
   Display display;
   
   ALLEGRO_TIMER* timer;
   ALLEGRO_EVENT_QUEUE* queue;
   
   bool keys_down[ALLEGRO_KEY_MAX];
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
         monitor_info(),
         adapter(-1),
         display(),
         timer(0),
         queue(0),
         keys_down(),
         fullscreen(false),
         redraw(true),
         quit(false),
         spiraloid_screen(),
         screens()
   {
      memset(keys_down , 0 , ALLEGRO_KEY_MAX*sizeof(bool));
      screens[0] = &spiraloid_screen;
      active_screen = 0;
   }
   
   int Init();

   void Run();
   
   
};





#endif // Program_HPP




