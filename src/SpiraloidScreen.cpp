

#include "SpiraloidScreen.hpp"



void SpiraloidScreen::SetKeyDownArray(bool* keys_down) {
   ProgramScreen::SetKeyDownArray(keys_down);
   this->keys_down = keys_down;
   spiraloid_controller.SetKeyDownArray(keys_down);
}



bool SpiraloidScreen::Init() {
   ResetScreen();
   return true;
}



bool SpiraloidScreen::HandleEvent(ALLEGRO_EVENT ev) {
   return spiraloid_controller.HandleInput(ev);
}



void SpiraloidScreen::Update(double dt) {
   spiraloid_controller.Update(dt);
}



void SpiraloidScreen::Draw() {
   spiraloid_controller.Draw();
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






