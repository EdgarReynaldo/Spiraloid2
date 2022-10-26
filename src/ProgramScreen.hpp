


#ifndef ProgramScreen_HPP
#define ProgramScreen_HPP


#include "Eagle/Events.hpp"

class EagleGraphicsContext;


class ProgramScreen {
   
public :
   ProgramScreen() {}
   virtual ~ProgramScreen() {}
   
   virtual bool Init()=0;
   
   virtual bool HandleEvent(EagleEvent ev)=0;
   virtual void Update(double dt)=0;
   virtual void Draw(EagleGraphicsContext* win)=0;
   
   virtual bool NeedsRedraw()=0;
   virtual void ResetScreen()=0;

};







#endif // ProgramScreen_HPP

