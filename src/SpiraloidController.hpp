


#ifndef SpiraloidController_HPP
#define SpiraloidController_HPP


#include "Spirals.hpp"
#include "NewDisplay.hpp"


#include "Eagle/Events.hpp"


class SpiraloidController {
   
private :
   Spiraloid* spiraloid;
   bool fullscreen;
   bool redraw;
   bool clear_buffer;
   bool temp_clear;

public :
   
   SpiraloidController();
   ~SpiraloidController();
   
   void ResetSpiraloid();
   
   void SetSpiraloidTransform(double cx , double cy , double sx , double sy);
   
   bool HandleInput(EagleEvent ev);
   void Update(double dt);
   void Draw(EagleGraphicsContext* win);
   
   bool NeedsRedraw() {return redraw;}
};

#endif // SpiraloidController_HPP









