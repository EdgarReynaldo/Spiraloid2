


#ifndef SpiraloidController_HPP
#define SpiraloidController_HPP


#include "Spirals.hpp"
#include "Display.hpp"
#include "Eagle.hpp"



class SpiraloidController {
   
private :
   Spiraloid* spiraloid;
   bool fullscreen;
   bool redraw;
   bool clear_buffer;
   bool temp_clear;
   bool paused;
   bool fix_the_center;
   double dt;
public :
   
   SpiraloidController();
   ~SpiraloidController();
   
   void SetRefresh(double dt);
   
   void ResetSpiraloid();
   
   void SetSpiraloidTransform(double cx , double cy , double sx , double sy);
   
   bool HandleInput(EagleEvent ev);
   void Update(double deltatime);
   void Draw(EagleGraphicsContext* win);
   
   bool NeedsRedraw() {return redraw;}
   
   Spiraloid* GetSpiraloid() {return spiraloid;}
};



#endif // SpiraloidController_HPP









