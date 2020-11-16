


#ifndef SpiraloidScreen_HPP
#define SpiraloidScreen_HPP

#include "ProgramScreen.hpp"
#include "SpiraloidController.hpp"




class SpiraloidScreen : public ProgramScreen {
   
   SpiraloidController spiraloid_controller;
   double dt;
   
   
public :
   
   void SetRefresh(double dt);
   
   SpiraloidScreen();
   
   virtual bool Init();
   
   virtual bool HandleEvent(EagleEvent ev);
   virtual void Update(double dt);
   virtual void Draw(EagleGraphicsContext* win);

   virtual bool NeedsRedraw();
   virtual void ResetScreen();

   void SetSpiraloidTransform(double cx , double cy , double sx , double sy);
   
   Spiraloid* GetSpiraloid() {return spiraloid_controller.GetSpiraloid();}
};



#endif // SpiraloidScreen_HPP





