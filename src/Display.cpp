

#include "Display.hpp"


#include <cstdio>

#include "allegro5/allegro_direct3d.h"



/// ------------------------     Display     ------------------------------------------




int Display::new_display_flags = EAGLE_DIRECT3D;
///int Display::new_display_flags = ALLEGRO_OPENGL;



bool Display::CreateWindowed(int wwidth , int wheight) {
   Destroy();
   fs = false;
   ww = wwidth;
   wh = wheight;
   display_flags = new_display_flags | EAGLE_RESIZABLE | EAGLE_WINDOWED;// | ALLEGRO_NOFRAME;
   win = a5sys->CreateGraphicsContext("Spiraloid" , ww , wh , display_flags);
   if (!win && win->Valid()) {
      return false;
   }
   return CreateBuffer(ww,wh);
}



bool Display::CreateFullScreen(int fswidth , int fsheight) {
   Destroy();
   fs = true;
   fsw = fswidth;
   fsh = fsheight;
   display_flags = new_display_flags | EAGLE_FULLSCREEN;
   win = a5sys->CreateGraphicsContext("Spiraloid" , fsw , fsh , display_flags);
   if (!win && win->Valid()) {
      return false;
   }
   return CreateBuffer(fsw,fsh);
}



void Display::DestroyBuffer() {
   if (buffer) {
      win->FreeImage(buffer);
      buffer = 0;
      bw = 0;
      bh = 0;
   }
}



Display::~Display() {
   Destroy();
}



void Display::Destroy() {
   DestroyBuffer();
   if (win) {
      a5sys->FreeGraphicsContext(win);
      win = 0;
   }
}



bool Display::Create(bool fullscreen , int fswidth , int fsheight , int wwidth , int wheight) {
   fsw = fswidth;
   fsh = fsheight;
   ww = wwidth;
   wh = wheight;
   if (fullscreen) {
      return CreateFullScreen(fswidth , fsheight);
   }
   else {
      return CreateWindowed(wwidth , wheight);
   }
}



bool Display::CreateBuffer(int bwidth , int bheight) {
   if (bwidth != bw || bheight != bh) {
      printf("Recreating buffer.\n");
      DestroyBuffer();
      bw = bwidth;
      bh = bheight;
      centerx = bw/2;
      centery = bh/2;
      scalex = (double)(fs?fsw:ww)/bw;
      scaley = (double)(fs?fsh:wh)/bh;
      buffer = dynamic_cast<Allegro5Image*>(win->CreateImage(bw , bh));
   }
   DrawToBuffer();
   return buffer;
   
}



void Display::AcknowledgeResize() {
   win->AcknowledgeResize();
   if (!fs) {
      ww = win->Width();
      wh = win->Height();
      CreateBuffer(ww,wh);
   }
}



bool Display::ToggleFullscreen() {
   return Create(!fs , fsw , fsh , ww , wh);
}



void Display::DrawToBuffer() {
   win->SetDrawingTarget(buffer);
}



void Display::Flip() {
   win->DrawToBackBuffer();
   al_draw_scaled_bitmap(buffer->AllegroBitmap() , 0 , 0 , bw , bh , 0 , 0 , fs?fsw:ww , fs?fsh:wh , 0);
//   al_draw_bitmap(buffer , 0 , 0 , 0);
   win->FlipDisplay();
}



bool Display::SaveScreenie() {
   do {
      sprintf(charbuf , "Screenie%d.png" , screenie_num++);
   } while (al_filename_exists(charbuf));
   return al_save_bitmap(charbuf , buffer->AllegroBitmap());
}



