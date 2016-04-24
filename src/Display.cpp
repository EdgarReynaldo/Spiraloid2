

#include "Display.hpp"


#include <cstdio>

#include "allegro5/allegro_direct3d.h"


int Display::new_display_flags = ALLEGRO_DIRECT3D;
///int Display::new_display_flags = ALLEGRO_OPENGL;



bool Display::CreateWindowed(int wwidth , int wheight) {
   Destroy();
   fs = false;
   ww = wwidth;
   wh = wheight;
   display_flags = new_display_flags | ALLEGRO_RESIZABLE | ALLEGRO_WINDOWED;// | ALLEGRO_NOFRAME;
   al_set_new_display_flags(display_flags);
   display = al_create_display(ww , wh);
   if (!display) {return false;}
   return CreateBuffer(ww,wh);
}



bool Display::CreateFullScreen(int fswidth , int fsheight) {
   Destroy();
   fs = true;
   fsw = fswidth;
   fsh = fsheight;
   display_flags = new_display_flags | ALLEGRO_FULLSCREEN;
   al_set_new_display_flags(display_flags);
   display = al_create_display(fsw , fsh);
   if (!display) {return false;}
   return CreateBuffer(fsw,fsh);
}



void Display::DestroyBuffer() {
   if (buffer) {
      al_destroy_bitmap(buffer);
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
   if (display) {
      al_destroy_display(display);
      display = 0;
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
   ///      al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
      al_set_target_backbuffer(display);
      buffer = al_create_bitmap(bw,bh);
   }
   DrawToBuffer();
   return buffer;
   
}



void Display::AcknowledgeResize() {
   al_acknowledge_resize(display);
   
   if (!fs) {
      ww = al_get_display_width(display);
      wh = al_get_display_height(display);
      CreateBuffer(ww,wh);
   }
}



bool Display::ToggleFullscreen() {
   return Create(!fs , fsw , fsh , ww , wh);
}



void Display::DrawToBuffer() {
   al_set_target_bitmap(buffer);
}



void Display::Flip() {
   al_set_target_backbuffer(display);
   al_draw_scaled_bitmap(buffer , 0 , 0 , bw , bh , 0 , 0 , fs?fsw:ww , fs?fsh:wh , 0);
//   al_draw_bitmap(buffer , 0 , 0 , 0);
   al_flip_display();
}



bool Display::SaveScreenie() {
   do {
      sprintf(charbuf , "Screenie%d.png" , screenie_num++);
   } while (al_filename_exists(charbuf));
   return al_save_bitmap(charbuf , buffer);
}



