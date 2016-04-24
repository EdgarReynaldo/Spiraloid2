



#include "SpiraloidController.hpp"

























void SpiraloidController::Draw() {
   if (redraw) {
      display->DrawToBuffer();
      if (clear_buffer || temp_clear) {
         al_clear_to_color(al_map_rgb(0,0,0));
         temp_clear = false;
      }
      spiraloid->Draw();
      display->Flip();
      
      redraw = false;
   }
}






