


#ifndef Display_HPP
#define Display_HPP

#include "allegro5/allegro.h"


#include <cmath>


class Display {
   static int new_display_flags;
   

   ALLEGRO_DISPLAY* display;
   ALLEGRO_BITMAP* buffer;
   
   bool fs;
   int display_flags;
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
   char charbuf[1024];


   bool CreateWindowed(int wwidth , int wheight);
   bool CreateFullScreen(int fswidth , int fsheight);

   void DestroyBuffer();

public :
///   Display();
   Display() :
         display(0),
         buffer(0),
         fs(false),
         display_flags(0),
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
         charbuf()
   {
      memset(charbuf , 0 , 1024);
   }
   
   ~Display();
   
   void Destroy();

   bool Create(bool fullscreen , int fswidth , int fsheight , int wwidth , int wheight);
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
   
   operator ALLEGRO_DISPLAY*() {return display;}
};

#endif // Display_HPP




