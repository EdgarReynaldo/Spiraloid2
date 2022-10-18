



#include "SpiraloidController.hpp"






SpiraloidController::SpiraloidController() :
      spiraloid(0),
      keys_down(0),
      fullscreen(false),
      redraw(true),
      clear_buffer(true),
      temp_clear(false)
{
   spiraloid = new Spiraloid;
}



SpiraloidController::~SpiraloidController() {
   delete spiraloid;
   spiraloid = 0;
}



void SpiraloidController::ResetSpiraloid() {
   spiraloid->Reset();
}



void SpiraloidController::SetSpiraloidTransform(double cx , double cy , double sx , double sy) {
   spiraloid->SetSpiraloidTransform(cx,cy,sx,sy);
}



bool SpiraloidController::HandleInput(ALLEGRO_EVENT ev) {

   if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
      keys_down[ev.keyboard.keycode] = true;
      if (ev.keyboard.keycode == ALLEGRO_KEY_I) {
         clear_buffer = !clear_buffer;
         redraw = true;
      }
      if (ev.keyboard.keycode == ALLEGRO_KEY_TAB) {
         if (keys_down[ALLEGRO_KEY_LSHIFT] || keys_down[ALLEGRO_KEY_RSHIFT]) {
            spiraloid->SpiralDrawingOptionValue()--;
         }
         else {
            spiraloid->SpiralDrawingOptionValue()++;
         }
      }
   }
   if (ev.type == ALLEGRO_EVENT_KEY_UP) {
      keys_down[ev.keyboard.keycode] = false;
   }

   if (ev.type == ALLEGRO_EVENT_TIMER) {
      double dt = al_get_timer_speed(ev.timer.source);
      redraw = true;
      
      if (keys_down[ALLEGRO_KEY_A]) {
         temp_clear = true;
         redraw = true;
      }

      /// SHIFT KEY MAKES OPTION CHANGES
      
      int modifier = 100;
      if (keys_down[ALLEGRO_KEY_LCTRL] || keys_down[ALLEGRO_KEY_RCTRL]) {
         modifier = 10;
      }
      if (keys_down[ALLEGRO_KEY_ALT] || keys_down[ALLEGRO_KEY_ALTGR]) {
         modifier = 1;
      }
      
      if (keys_down[ALLEGRO_KEY_LSHIFT] || keys_down[ALLEGRO_KEY_RSHIFT]) {
   //               printf("Key SHIFT down\n");
   ///               double dold_dps = spiraloid.RotationDPSValue();
   ///               int old_dps = spiraloid.RotationDPSValue().IVal();
         if (keys_down[ALLEGRO_KEY_PAD_3] || keys_down[ALLEGRO_KEY_PAD_1]) {
   //                  printf("Rotation key down\n");
            if (keys_down[ALLEGRO_KEY_PAD_3]) {
               spiraloid->RotationDPSValue() += modifier;
            }
            if (keys_down[ALLEGRO_KEY_PAD_1]) {
               spiraloid->RotationDPSValue() -= modifier;
            }
   ///                  double d_dps = spiraloid->RotationDPSValue();
   ///                  int dps = spiraloid->RotationDPSValue()->IVal();
   //                  printf("RotationDPSValue : IVal (%d , %d) , DVal (%14.8lf , %14.8lf) , modifier (%d)\n" , old_dps , dps , dold_dps , d_dps , modifier);
         }
      }
      else {
         if (keys_down[ALLEGRO_KEY_PAD_3]) {
            spiraloid->RotationDegreesValue() += modifier;
         }
         if (keys_down[ALLEGRO_KEY_PAD_1]) {
            spiraloid->RotationDegreesValue() -= modifier;
         }
      }

      int spiral_option = spiraloid->SpiralDrawingOptionValue().IVal();
      if (keys_down[ALLEGRO_KEY_OPENBRACE]) {
         if (spiral_option == SPIRAL_CIRCLE) {
            spiraloid->CircleRadiusValue() -= modifier;
         }
         else if (spiral_option == SPIRAL_RHOMBUS || spiral_option == SPIRAL_OCTAGON) {
            if (keys_down[ALLEGRO_KEY_LSHIFT] || keys_down[ALLEGRO_KEY_RSHIFT]) {
               spiraloid->RhombusYScaleValue() -= modifier;
            }
            else {
               spiraloid->RhombusXScaleValue() -= modifier;
            }
         }
      }
      if (keys_down[ALLEGRO_KEY_CLOSEBRACE]) {
         if (spiral_option == SPIRAL_CIRCLE) {
            spiraloid->CircleRadiusValue() += modifier;
         }
         else if (spiral_option == SPIRAL_RHOMBUS || spiral_option == SPIRAL_OCTAGON) {
            if (keys_down[ALLEGRO_KEY_LSHIFT] || keys_down[ALLEGRO_KEY_RSHIFT]) {
               spiraloid->RhombusYScaleValue() += modifier;
            }
            else {
               spiraloid->RhombusXScaleValue() += modifier;
            }
         }
      }
      if (spiral_option == SPIRAL_OCTAGON) {
         if (keys_down[ALLEGRO_KEY_MINUS]) {
            spiraloid->RhombusDiagScaleValue() -= modifier;
         }
         if (keys_down[ALLEGRO_KEY_EQUALS]) {
            spiraloid->RhombusDiagScaleValue() += modifier;
         }
      }

      /// SHIFT KEY NOW MAKES MODIFIER 1000

      if (keys_down[ALLEGRO_KEY_LSHIFT] || keys_down[ALLEGRO_KEY_RSHIFT]) {
         modifier = 1000;
      }


      if (keys_down[ALLEGRO_KEY_PAD_6]) {
         spiraloid->ThetaDeltaValue() += modifier;
      }
      if (keys_down[ALLEGRO_KEY_PAD_4]) {
         spiraloid->ThetaDeltaValue() -= modifier;
      }
      if (keys_down[ALLEGRO_KEY_PAD_PLUS]) {
         spiraloid->ThetaOffsetValue() += modifier;
      }
      if (keys_down[ALLEGRO_KEY_PAD_MINUS]) {
         spiraloid->ThetaOffsetValue() -= modifier;
      }
      if (keys_down[ALLEGRO_KEY_COMMA]) {
         spiraloid->LineThicknessValue() -= modifier;
         printf("LTV == %8.4lf\n" , (double)spiraloid->LineThicknessValue());
      }
      if (keys_down[ALLEGRO_KEY_FULLSTOP]) {
         spiraloid->LineThicknessValue() += modifier;
         printf("LTV == %8.4lf\n" , (double)spiraloid->LineThicknessValue());
      }
      
      Update(dt);
   }
   return false;
}






void SpiraloidController::Update(double dt) {
   spiraloid->Update(dt);
}




void SpiraloidController::Draw() {
   spiraloid->Refresh();
   if (redraw) {
      if (clear_buffer || temp_clear) {
         al_clear_to_color(al_map_rgb(0,0,255));
         temp_clear = false;
      }
      spiraloid->Draw();
      
      redraw = false;
   }
}






