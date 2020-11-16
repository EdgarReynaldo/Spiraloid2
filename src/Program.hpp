




#ifndef Program_HPP
#define Program_HPP



#include "Eagle/backends/Allegro5Backend.hpp"
#include "Eagle.hpp"



#include "Monitors.hpp"
#include "Display.hpp"
#include "SpiraloidController.hpp"
#include "SpiraloidScreen.hpp"
#include "ColorScreen.hpp"


class Program {
   
private :
   Allegro5System* a5sys;
   EagleGraphicsContext* win;
   EagleTimer* timer;
   EagleEventHandler* queue;
//   EagleImage* buffer;

   
   MonitorInfo monitor_info;
   
   int adapter;
   Display display;
   
   
   bool fullscreen;
   bool redraw;
   bool quit;
   int init_state;
   
   #define NUM_SCREENS 2
   SpiraloidScreen* spiraloid_screen;
   ColorScreen* color_screen;
   
   ProgramScreen* screens[NUM_SCREENS];
   int active_screen;
public :
   
   Program();

   ~Program();
   
   
protected :
   int Init();
public :
   void Run();
   
   int InitState() {return init_state;}
};





#endif // Program_HPP




