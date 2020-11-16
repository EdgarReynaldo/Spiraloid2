



#include "ColorPicker.hpp"




/// --------------------------------------      ColorPicker     ----------------------------------------




const unsigned int TOPIC_COLOR_PICKER = NextFreeTopicId();




void ColorPicker::DrawPickerBuf() {
   
   win->PushDrawingTarget(buf);
   win->Clear();

   /// HSL picker is a 2D Hue / Saturation rectangle

   bool on = true;
   const int sqsize = 5;
   int i = 0;
   const unsigned int w = buf->W();
   const unsigned int h = buf->H();
   ALLEGRO_LOCKED_REGION* rg = al_lock_bitmap(buf->AllegroBitmap() , ALLEGRO_PIXEL_FORMAT_RGBA_8888 , ALLEGRO_LOCK_READWRITE);
   (void)rg;
   for (unsigned int y = 0 ; y < h ; ++y) {
      const float sat = ((h-1)-y)/(float)(h-1);
      if (y/sqsize % 2 == 0) {
         on = !on;
      }
      for (unsigned int x = 0 ; x < w ; ++x) {
         if (x % sqsize == 0) {
            on = !on;
         }
         float hue = (x/(float)(w-1))*360.0;
         float r,g,b;
         al_color_hsl_to_rgb(hue , sat , l , &r , &g , &b);
         r *= (float)a;
         g *= (float)a;
         b *= (float)a;
         /// Draw checkerboard so alpha shows through
         al_put_pixel(x , y , (on?al_map_rgb(255,255,255):al_map_rgb(0,0,0)));
         al_put_blended_pixel(x , y , al_map_rgba_f(r,g,b,a));
         ++i;
      }
   }
   al_unlock_bitmap(buf->AllegroBitmap());
   win->PopDrawingTarget();

   buf_drawn = true;
}



int ColorPicker::PrivateHandleEvent(EagleEvent ee) {
   if (ee.type == EAGLE_EVENT_MOUSE_BUTTON_DOWN) {
      if (InnerArea().Contains(ee.mouse.x , ee.mouse.y)) {
            
         /// We know the hue and saturation from the position on the bitmap
         
         /// We know the lightness and alpha from user settings
         float hue = (ee.mouse.x - InnerArea().X())/(float)(InnerArea().W());
         float sat = (InnerArea().H() - (InnerArea().Y() - ee.mouse.y))/(float)(InnerArea().H());
         if (hue < 0.0f) {hue = 0.0f;}
         if (hue > 1.0f) {hue = 1.0f;}
         if (sat < 0.0f) {sat = 0.0f;}
         if (sat > 1.0f) {sat = 1.0f;}
         h = hue;
         s = sat;
         unsigned char r,g,b;
         if (sat < 0.01f) {
            int gray = (int)(255.0f*l);
            r = g = b = gray;
         }
         else {
            al_unmap_rgb(al_color_hsl(h,s,l) , &r , &g , &b);
         }
         r *= (float)a;
         g *= (float)a;
         b *= (float)a;
         col.SetColor(r,g,b,a,false);
/**
         int x = InnerArea().X() - ee.mouse.x;
         int y = InnerArea().Y() - ee.mouse.y;
         ALLEGRO_LOCKED_REGION rg = al_lock_bitmap_region(buf->AllegroBitmap() , x , y , 1 , 1 , ALLEGRO_PIXEL_FORMAT_RGBA_8888 , ALLEGRO_LOCK_READONLY);
         unsigned char r,g,b,a;
         r = ((unsigned char*)rg->data)[0];
         g = ((unsigned char*)rg->data)[1];
         b = ((unsigned char*)rg->data)[2];
         a = ((unsigned char*)rg->data)[3];
         col.SetColor(r,g,b,a);
         al_unlock_bitmap(buf->AllegroBitmap());
*/
         QueueUserMessage(WidgetMsg(this , TOPIC_COLOR_PICKER , COLOR_CHANGED));
         return DIALOG_INPUT_USED;
      }
   }
   return DIALOG_OKAY;
}



int ColorPicker::PrivateCheckInputs() {
   return DIALOG_OKAY;
}



int ColorPicker::PrivateUpdate(double dt) {
   (void)dt;
   return DIALOG_OKAY;
}



void ColorPicker::PrivateDisplay(EagleGraphicsContext* win , int xpos , int ypos) {
   if (!buf_drawn) {
      DrawPickerBuf();
   }
   win->Draw(buf , InnerArea().X() + xpos , InnerArea().Y() + ypos);
}



void ColorPicker::OnAreaChanged() {
   if (!buf || (buf && !buf->Valid())) {
      buf = dynamic_cast<Allegro5Image*>(win->CreateImage(InnerArea().W() , InnerArea().H() , VIDEO_IMAGE , "Color picker buffer"));
      EAGLE_ASSERT(buf && buf->Valid());
   }
   buf->Allocate(InnerArea().W() , InnerArea().H());
   buf_drawn = false;
   SetRedrawFlag();
}



ColorPicker::ColorPicker(EagleGraphicsContext* window) :
      WidgetBase("ColorPicker" , "HueSatPicker"),
      win(window),
      h(0.0f),
      s(1.0f),
      l(0.5f),
      a(1.0f),
      col(),
      buf(0),
      buf_drawn(false)
{}




ColorPicker::~ColorPicker() {
   if (buf) {
      win->FreeImage(buf);
      buf = 0;
   }
}




void ColorPicker::SetColors(float lightness , float alpha) {
   l = lightness;
   a = alpha;
   SetRedrawFlag();
}



float ColorPicker::HuePick() {
   return h;
}



float ColorPicker::SatPick() {
   return s;
}



EagleColor ColorPicker::GetEagleColor() {
   return col;
}






