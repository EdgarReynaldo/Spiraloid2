



#include "SpiraloidController.hpp"

#include "Eagle/InputHandler.hpp"





SpiraloidController::SpiraloidController() :
      spiraloid(0),
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



bool SpiraloidController::HandleInput(EagleEvent ev) {

   if (ev.type == EAGLE_EVENT_KEY_DOWN) {
      if (ev.keyboard.keycode == EAGLE_KEY_I) {
         clear_buffer = !clear_buffer;
         redraw = true;
      }
      if (ev.keyboard.keycode == EAGLE_KEY_TAB) {
         if (keydown[EAGLE_KEY_LSHIFT] || keydown[EAGLE_KEY_RSHIFT]) {
            spiraloid->SpiralDrawingOptionValue()--;
         }
         else {
            spiraloid->SpiralDrawingOptionValue()++;
         }
      }
   }

   if (ev.type == EAGLE_EVENT_TIMER) {
      double dt = ev.timer.eagle_timer_source->SPT();
      redraw = true;
      
      if (keydown[EAGLE_KEY_A]) {
         temp_clear = true;
         redraw = true;
      }

      /// SHIFT KEY MAKES OPTION CHANGES
      
      int modifier = 100;
      if (keydown[EAGLE_KEY_LCTRL] || keydown[EAGLE_KEY_RCTRL]) {
         modifier = 10;
      }
      if (keydown[EAGLE_KEY_ALT] || keydown[EAGLE_KEY_ALTGR]) {
         modifier = 1;
      }
      
      if (keydown[EAGLE_KEY_LSHIFT] || keydown[EAGLE_KEY_RSHIFT]) {
   //               printf("Key SHIFT down\n");
   ///               double dold_dps = spiraloid.RotationDPSValue();
   ///               int old_dps = spiraloid.RotationDPSValue().IVal();
         if (keydown[EAGLE_KEY_PAD_3] || keydown[EAGLE_KEY_PAD_1]) {
   //                  printf("Rotation key down\n");
            if (keydown[EAGLE_KEY_PAD_3]) {
               spiraloid->RotationDPSValue() += modifier;
            }
            if (keydown[EAGLE_KEY_PAD_1]) {
               spiraloid->RotationDPSValue() -= modifier;
            }
   ///                  double d_dps = spiraloid->RotationDPSValue();
   ///                  int dps = spiraloid->RotationDPSValue()->IVal();
   //                  printf("RotationDPSValue : IVal (%d , %d) , DVal (%14.8lf , %14.8lf) , modifier (%d)\n" , old_dps , dps , dold_dps , d_dps , modifier);
         }
      }
      else {
         if (keydown[EAGLE_KEY_PAD_3]) {
            spiraloid->RotationDegreesValue() += modifier;
         }
         if (keydown[EAGLE_KEY_PAD_1]) {
            spiraloid->RotationDegreesValue() -= modifier;
         }
      }

      int spiral_option = spiraloid->SpiralDrawingOptionValue().IVal();
      if (keydown[EAGLE_KEY_OPENBRACE]) {
         if (spiral_option == SPIRAL_CIRCLE) {
            spiraloid->CircleRadiusValue() -= modifier;
         }
         else if (spiral_option == SPIRAL_RHOMBUS || spiral_option == SPIRAL_OCTAGON) {
            if (keydown[EAGLE_KEY_LSHIFT] || keydown[EAGLE_KEY_RSHIFT]) {
               spiraloid->RhombusYScaleValue() -= modifier;
            }
            else {
               spiraloid->RhombusXScaleValue() -= modifier;
            }
         }
      }
      if (keydown[EAGLE_KEY_CLOSEBRACE]) {
         if (spiral_option == SPIRAL_CIRCLE) {
            spiraloid->CircleRadiusValue() += modifier;
         }
         else if (spiral_option == SPIRAL_RHOMBUS || spiral_option == SPIRAL_OCTAGON) {
            if (keydown[EAGLE_KEY_LSHIFT] || keydown[EAGLE_KEY_RSHIFT]) {
               spiraloid->RhombusYScaleValue() += modifier;
            }
            else {
               spiraloid->RhombusXScaleValue() += modifier;
            }
         }
      }
      if (spiral_option == SPIRAL_OCTAGON) {
         if (keydown[EAGLE_KEY_MINUS]) {
            spiraloid->RhombusDiagScaleValue() -= modifier;
         }
         if (keydown[EAGLE_KEY_EQUALS]) {
            spiraloid->RhombusDiagScaleValue() += modifier;
         }
      }

      /// SHIFT KEY NOW MAKES MODIFIER 1000

      if (keydown[EAGLE_KEY_LSHIFT] || keydown[EAGLE_KEY_RSHIFT]) {
         modifier = 1000;
      }


      if (keydown[EAGLE_KEY_PAD_6]) {
         spiraloid->ThetaDeltaValue() += modifier;
      }
      if (keydown[EAGLE_KEY_PAD_4]) {
         spiraloid->ThetaDeltaValue() -= modifier;
      }
      if (keydown[EAGLE_KEY_PAD_PLUS]) {
         spiraloid->ThetaOffsetValue() += modifier;
      }
      if (keydown[EAGLE_KEY_PAD_MINUS]) {
         spiraloid->ThetaOffsetValue() -= modifier;
      }
      if (keydown[EAGLE_KEY_COMMA]) {
         spiraloid->LineThicknessValue() -= modifier;
      }
      if (keydown[EAGLE_KEY_FULLSTOP]) {
         spiraloid->LineThicknessValue() += modifier;
      }
      
      Update(dt);
   }
   return false;
}






void SpiraloidController::Update(double dt) {
   spiraloid->Update(dt);
}




void SpiraloidController::Draw(EagleGraphicsContext* win) {
   spiraloid->Refresh();
   if (redraw) {
      if (clear_buffer || temp_clear) {
         win->Clear(EagleColor(0,0,255);
         temp_clear = false;
      }
      spiraloid->Draw(win);
      
      redraw = false;
   }
}






