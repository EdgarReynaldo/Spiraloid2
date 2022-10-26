

#include "NewDisplay.hpp"


#include <cstdio>

#include "Eagle/backends/Allegro5Backend.hpp"
#include "Eagle/Exception.hpp"
#include "Eagle/Image.hpp"
#include "Eagle/StringWork.hpp"



/// ------------------------     Display     ------------------------------------------




bool NewDisplay::CreateWindowed(int wwidth , int wheight , int newflags) {
   Destroy();
   fs = false;
   ww = wwidth;
   wh = wheight;
   flags = newflags | ALLEGRO_RESIZABLE | ALLEGRO_WINDOWED;// | ALLEGRO_NOFRAME;
   win = dynamic_cast<Allegro5GraphicsContext*>(sys->CreateGraphicsContext("Spirloid" , ww , wh , flags));
   EAGLE_ASSERT(win && win->Valid());

   return CreateBuffer(ww,wh);
}



bool NewDisplay::CreateFullScreen(int fswidth , int fsheight , int newflags) {
   Destroy();
   fs = true;
   fsw = fswidth;
   fsh = fsheight;
   flags = newflags | ALLEGRO_FULLSCREEN_WINDOW;
   win = dynamic_cast<Allegro5GraphicsContext*>(sys->CreateGraphicsContext("Spiraloid" , fsw , fsh , flags));
   EAGLE_ASSERT(win && win->Valid());
   
   return CreateBuffer(fsw,fsh);
}



void NewDisplay::DestroyBuffer() {
   if (buf) {
      win->FreeImage(buf);
      buf = 0;
   }
}



NewDisplay::~NewDisplay() {
   Destroy();
}



void NewDisplay::Destroy() {
   DestroyBuffer();
   if (win) {
      sys->FreeGraphicsContext(win);
      win = 0;
   }
}



bool NewDisplay::Create(EagleSystem* system , bool fullscreen , int fswidth , int fsheight , int wwidth , int wheight , int flags) {
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



bool NewDisplay::CreateBuffer(int bwidth , int bheight) {
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



void NewDisplay::AcknowledgeResize() {
   win->AcknowledgeResize();
   
   if (!fs) {
      ww = win->Width();
      wh = win->Height();
      CreateBuffer(ww,wh);
   }
}



bool NewDisplay::ToggleFullscreen() {
   return Create(sys , !fs , fsw , fsh , ww , wh , flags);
}



void NewDisplay::DrawToBuffer() {
   win->SetDrawingTarget(buf);
}



void NewDisplay::Flip() {
   win->DrawToBackBuffer();
   win->DrawStretched(buf , Rectangle(0 , 0 , fs?fsw:ww , fs?fsh:wh));
   win->FlipDisplay();
}



bool NewDisplay::SaveScreenie() {
   do {
      textbuf = StringPrintF("Screenie%d.png" , screenie_num++);
   } while (al_filename_exists(textbuf.c_str()));
   bool ret = win->SaveImage(buf , textbuf);
   return ret;
}



EagleGraphicsContext* NewDisplay::GetDisplay() {
   return dynamic_cast<EagleGraphicsContext*>(win);
}






