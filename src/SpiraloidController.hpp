


#ifndef SpiraloidController_HPP
#define SpiraloidController_HPP


#include "Spirals.hpp"
#include "Display.hpp"


enum {
   
};

class InputAction {
   
   
   
   
};


class SpiraloidController {
   
private :
   Spiraloid* spiraloid;
   bool* keys_down;
   bool fullscreen;
   bool redraw;
   bool clear_buffer;
   bool temp_clear;

public :
   
   SpiraloidController();
   ~SpiraloidController();
   
   void SetKeyDownArray(bool* keys_down) {this->keys_down = keys_down;}
   void ResetSpiraloid();
   
   void SetSpiraloidTransform(double cx , double cy , double sx , double sy);
   
   bool HandleInput(ALLEGRO_EVENT ev);
   void Update(double dt);
   void Draw();
   
   bool NeedsRedraw() {return redraw;}
};

#endif // SpiraloidController_HPP









