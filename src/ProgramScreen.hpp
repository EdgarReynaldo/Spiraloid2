


#ifndef ProgramScreen_HPP
#define ProgramScreen_HPP


#include "allegro5/allegro.h"



class ProgramScreen {
   
protected :
   bool* keys_down;
   
public :
   ProgramScreen() : keys_down(0) {}
   
   virtual void SetKeyDownArray(bool* keys_down) {this->keys_down = keys_down;}

   virtual ~ProgramScreen() {}
   
   virtual bool Init()=0;
   
   virtual bool HandleEvent(ALLEGRO_EVENT ev)=0;
   virtual void Update(double dt)=0;
   virtual void Draw()=0;
   
   virtual bool NeedsRedraw()=0;
   virtual void ResetScreen()=0;

};







#endif // ProgramScreen_HPP

