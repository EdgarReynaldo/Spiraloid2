


#ifndef Display_HPP
#define Display_HPP

#include "allegro5/allegro.h"


#include <cmath>

class EagleSystem;
class Allegro5GraphicsContext;
class EagleImage;



class Display {
   
   EagleSystem* sys;
   Allegro5GraphicsContext* win;
   EagleImage* buf;
   
   bool fs;
   int flags;
   int fsw;
   int fsh;
   int ww;
   int wh;
   int bw;
   int bh;

   double centerx;
   double centery;
   double scalex;
   double scaley;
   
   int screenie_num;
   int monitor_num;
   std::string textbuf;

   bool CreateWindowed(int wwidth , int wheight);
   bool CreateFullScreen(int fswidth , int fsheight);

   void DestroyBuffer();

public :
///   Display();
   Display() :
         sys(0),
         win(0),
         buf(0),
         fs(false),
         flags(0),
         fsw(0),
         fsh(0),
         ww(0),
         wh(0),
         bw(0),
         bh(0),
         centerx(0.0),
         centery(0.0),
         scalex(1.0),
         scaley(1.0),
         screenie_num(0),
         monitor_num(0),
         textbuf()
   {
   }
   
   ~Display();
   
   void Destroy();

   bool Create(EagleSystem* sys , bool fullscreen , int fswidth , int fsheight , int wwidth , int wheight , int newflags);
   bool CreateBuffer(int bwidth , int bheight);

   void AcknowledgeResize();
   
   bool ToggleFullscreen();
   
   void DrawToBuffer();
   void Flip();

   bool SaveScreenie();
   
   double CX() {return centerx;}
   double CY() {return centery;}
   double SX() {return scalex;}
   double SY() {return scaley;}
   double W() {return fs?fsw:ww;}
   double H() {return fs?fsh:wh;}
   double Diag() {return sqrt(W()*W() + H()*H());}
   
   EagleGraphicsContext* GetDisplay() {return win;}
};

#endif // Display_HPP




