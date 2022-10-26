

#include "SpiraloidScreen.hpp"



bool SpiraloidScreen::Init() {
   ResetScreen();
   return true;
}



bool SpiraloidScreen::HandleEvent(EagleEvent ev) {
   return spiraloid_controller.HandleInput(ev);
}



void SpiraloidScreen::Update(double dt) {
   spiraloid_controller.Update(dt);
}



void SpiraloidScreen::Draw(EagleGraphicsContext* win) {
   spiraloid_controller.Draw(win);
}



bool SpiraloidScreen::NeedsRedraw() {
   return spiraloid_controller.NeedsRedraw();
}



void SpiraloidScreen::ResetScreen() {
   spiraloid_controller.ResetSpiraloid();
}



void SpiraloidScreen::SetSpiraloidTransform(double cx , double cy , double sx , double sy) {
   spiraloid_controller.SetSpiraloidTransform(cx,cy,sx,sy);
}






