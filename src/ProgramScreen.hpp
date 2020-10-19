


#ifndef ProgramScreen_HPP
#define ProgramScreen_HPP

#include "Eagle.hpp"


#include "allegro5/allegro.h"



class ProgramScreen {
   
public :
   virtual ~ProgramScreen() {}
   
   virtual bool Init()=0;
   
   virtual bool HandleEvent(EagleEvent ev)=0;
   virtual void Update(double dt)=0;
   virtual void Draw()=0;
   
   virtual bool NeedsRedraw()=0;
   virtual void ResetScreen()=0;

};



#endif // ProgramScreen_HPP





