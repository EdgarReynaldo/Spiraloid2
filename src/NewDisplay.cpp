

#include "Display.hpp"


#include <cstdio>

#include "allegro5/allegro_direct3d.h"



/// ------------------------     Display     ------------------------------------------




bool Display::CreateWindowed(int wwidth , int wheight , int newflags) {
   Destroy();
   fs = false;
   ww = wwidth;
   wh = wheight;
   flags = newflags | ALLEGRO_RESIZABLE | ALLEGRO_WINDOWED;// | ALLEGRO_NOFRAME;
   win = sys->CreateGraphicsContext("Spirloid" , ww , wh , flags);
   EAGLE_ASSERT(win && win->Valid());

   return CreateBuffer(ww,wh);
}



bool Display::CreateFullScreen(int fswidth , int fsheight , int newflags) {
   Destroy();
   fs = true;
   fsw = fswidth;
   fsh = fsheight;
   flags = newflags | ALLEGRO_FULLSCREEN_WINDOW;
   win = sys->CreateGraphicsContext("Spiraloid" , fsw , fsh , flags);
   EAGLE_ASSERT(win && win->Valid());
   
   return CreateBuffer(fsw,fsh);
}



void Display::DestroyBuffer() {
   if (buf) {
      win->FreeImage(buf);
      buf = 0;
   }
}



Display::~Display() {
   Destroy();
}



void Display::Destroy() {
   DestroyBuffer();
   if (win) {
      sys->FreeGraphicsContext(win);
      win = 0;
   }
}



bool Display::Create(EagleSystem* system , bool fullscreen , int fswidth , int fsheight , int wwidth , int wheight , int flags) {
   EAGLE_ASSERT(system);
   sys = system;
   fsw = fswidth;
   fsh = fsheight;
   ww = wwidth;
   wh = wheight;
   if (fullscreen) {
      return CreateFullScreen(fswidth , fsheight , flags);
   }
   else {
      return CreateWindowed(wwidth , wheight , flags);
   }
}



bool Display::CreateBuffer(int bwidth , int bheight) {
   EAGLE_ASSERT(win);
   
   if (bwidth != bw || bheight != bh) {
      printf("Recreating buffer.\n");
      DestroyBuffer();
      bw = bwidth;
      bh = bheight;
      centerx = bw/2;
      centery = bh/2;
      scalex = (double)(fs?fsw:ww)/bw;
      scaley = (double)(fs?fsh:wh)/bh;
   ///      al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
      buf = win->CreateImage(bw , bh);
      EAGLE_ASSERT(buf && buf->Valid());
   }
   DrawToBuffer();
   return buf && buf->Valid();
}



void Display::AcknowledgeResize() {
   win->AcknowedgeResize();
   
   if (!fs) {
      ww = win->Width();
      wh = win->Height();
      CreateBuffer(ww,wh);
   }
}



bool Display::ToggleFullscreen() {
   return Create(!fs , fsw , fsh , ww , wh , flags);
}



void Display::DrawToBuffer() {
   win->DrawTo(buf);
}



void Display::Flip() {
   win->DrawToBackbuffer();
   win->DrawScaled(buf , 0 , 0 , bw , bh , 0 , 0 , fs?fsw:ww , fs?fsh:wh);
   win->FlipDisplay();
}



bool Display::SaveScreenie() {
   do {
      textbuf = StringPrintF("Screenie%d.png" , screenie_num++);
   } while (al_filename_exists(textbuf.c_str()));
   bool ret = win->SaveImage(buf);
   return ret;
}



operator ALLEGRO_DISPLAY*() {
   if (!win) {return 0;}
   return win->GetAllegroDisplay();
}







