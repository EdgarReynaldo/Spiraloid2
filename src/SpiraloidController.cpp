



#include "SpiraloidController.hpp"






SpiraloidController::SpiraloidController() :
      spiraloid(0),
      fullscreen(false),
      redraw(true),
      clear_buffer(true),
      temp_clear(false),
      paused(false),
      fix_the_center(true),
      dt(0.0)
{
   spiraloid = new Spiraloid;
   spiraloid->FixTheCenter(fix_the_center);
}



SpiraloidController::~SpiraloidController() {
   delete spiraloid;
   spiraloid = 0;
}



void SpiraloidController::SetRefresh(double dt) {
   this->dt = dt;
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
      if (ev.keyboard.keycode == EAGLE_KEY_E) {
         fix_the_center = !fix_the_center;
         spiraloid->FixTheCenter(fix_the_center);
      }
      if (ev.keyboard.keycode == EAGLE_KEY_P) {
         paused = !paused;
      }
      if (ev.keyboard.keycode == EAGLE_KEY_ENTER) {
         if (input_key_held(EAGLE_KEY_NO_MOD)) {
            spiraloid->RotationDPSValue() = 0;
            spiraloid->ColorCycleRate() = 0;
         }
         else if (input_key_held(EAGLE_KEY_ANY_ALT)) {
            spiraloid->Reset();
         }
         else if (input_key_held(EAGLE_KEY_ANY_SHIFT)) {
            /// Open color screen TODO
         }
         else if (input_key_held(EAGLE_KEY_ANY_CTRL)) {
            /// Open settings screen TODO
         }
      }
      if (ev.keyboard.keycode == EAGLE_KEY_F && input_key_held(EAGLE_KEY_NO_MOD)) {
         spiraloid->FlipColors(!spiraloid->Flip());
      }
      if (ev.keyboard.keycode == EAGLE_KEY_C) {
         spiraloid->CycleColors(!spiraloid->ColorCycle());
      }
   }

   if (ev.type == EAGLE_EVENT_KEY_DOWN) {
      if (ev.keyboard.keycode == EAGLE_KEY_LSHIFT ||
          ev.keyboard.keycode == EAGLE_KEY_RSHIFT ||
          ev.keyboard.keycode == EAGLE_KEY_RCTRL ||
          ev.keyboard.keycode == EAGLE_KEY_LCTRL ||
          ev.keyboard.keycode == EAGLE_KEY_ALT ||
          ev.keyboard.keycode == EAGLE_KEY_ALTGR) {
         return false;
      }
   }
   if ((!paused && ev.type == EAGLE_EVENT_TIMER) || (paused && ev.type == EAGLE_EVENT_KEY_CHAR) || (paused && ev.type == EAGLE_EVENT_KEY_DOWN)) {

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
         if (keydown[EAGLE_KEY_PAD_3] || keydown[EAGLE_KEY_PAD_1]) {
            if (keydown[EAGLE_KEY_PAD_3]) {
               spiraloid->RotationDPSValue() += modifier;
            }
            if (keydown[EAGLE_KEY_PAD_1]) {
               spiraloid->RotationDPSValue() -= modifier;
            }
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
      
      /// Alter color cycling
      
      if (keydown[EAGLE_KEY_X]) {
         spiraloid->ColorIndexStartValue() -= modifier;
         spiraloid->Refresh();
      }

      if (keydown[EAGLE_KEY_V]) {
         spiraloid->ColorIndexStartValue() += modifier;
         spiraloid->Refresh();
      }

      if (keydown[EAGLE_KEY_Z]) {
         spiraloid->ColorCycleRate() -= modifier;
         spiraloid->Refresh();
      }

      if (keydown[EAGLE_KEY_B]) {
         spiraloid->ColorCycleRate() += modifier;
         spiraloid->Refresh();
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
         printf("LTV == %8.4lf\n" , (double)spiraloid->LineThicknessValue());
      }
      if (keydown[EAGLE_KEY_FULLSTOP]) {
         spiraloid->LineThicknessValue() += modifier;
         printf("LTV == %8.4lf\n" , (double)spiraloid->LineThicknessValue());
      }
      
      if (keydown[EAGLE_KEY_UP]) {
         spiraloid->NumShades() += modifier;
         spiraloid->RefreshColors();
      }
      if (keydown[EAGLE_KEY_DOWN]) {
         spiraloid->NumShades() -= modifier;
         spiraloid->RefreshColors();
      }
      if (keydown[EAGLE_KEY_PAD_SLASH]) {
         spiraloid->RadialDeltaValue() -= modifier;
         spiraloid->Refresh();
      }
      if (keydown[EAGLE_KEY_PAD_ASTERISK]) {
         spiraloid->RadialDeltaValue() += modifier;
         spiraloid->Refresh();
      }
      
      Update(dt);
   }
   return false;
}






void SpiraloidController::Update(double deltatime) {
   spiraloid->Update(deltatime);
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






