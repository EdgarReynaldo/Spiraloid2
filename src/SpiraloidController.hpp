


#ifndef SpiraloidController_HPP
#define SpiraloidController_HPP


enum {
   
};

class InputAction {
   
   
   
   
};


class SpiraloidController {
   
private :
   
   Spiraloid* spiraloid;
   Display* display;
   
   bool redraw;
   bool clear_buffer;
   bool temp_clear;



public :
   
   
   
   void ResetSpiraloid();
   void ResetSpiraloid() {
      
      double radius = 100.0;
      double theta_start = 0.0;
      double theta_stop = 360.0*25.0;
      double theta_diff = 1.0;
      double theta_offset = 360.0;
      
      double rotation_degrees = 0.0;
      
      spiraloid->SetSpiraloidParameters(radius , theta_start , theta_stop , theta_diff , theta_offset);
      spiraloid->SetSpiraloidTransform(display.CX() , display.CY() , display.SX() , display.SY());
      spiraloid->SetRotation(rotation_degrees);
      spiraloid->Refresh();

   }
   
   
   
   
   
   
   void HandleInput(ALLEGRO_EVENT ev);
   void Update(double dt);
   void Draw();

void SpiraloidController::HandleInput(ALLEGRO_EVENT ev) {
   
}
void SpiraloidController::Update(double dt) {
   
}
   
};

#endif // SpiraloidController_HPP









