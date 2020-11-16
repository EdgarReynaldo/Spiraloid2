



#ifndef ColorPicker_HPP
#define ColorPicker_HPP



#include "Eagle.hpp"
#include "Eagle/backends/Allegro5Backend.hpp"
#include "allegro5/allegro_color.h"



extern const unsigned int TOPIC_COLOR_PICKER;

enum COLOR_PICKER_MSGS {
   COLOR_CHANGED = 1
};




class ColorPicker : public WidgetBase {
   
   EagleGraphicsContext* win;
   float h,s,l,a;
   EagleColor col;
   Allegro5Image* buf;
   bool buf_drawn;
   
   /// Private interface, override to define behavior
   virtual int PrivateHandleEvent(EagleEvent ee);
   virtual int PrivateCheckInputs();
   virtual int PrivateUpdate(double dt);
   virtual void PrivateDisplay(EagleGraphicsContext* win , int xpos , int ypos);

   /// Callbacks, override and/or call if you need to
   virtual void OnAreaChanged();


   void DrawPickerBuf();


public :
   ColorPicker(EagleGraphicsContext* window);
   ~ColorPicker();

   void SetColors(float lightness , float alpha);
//   void SetColors(float hue , float sat , float light , float alpha);
   void SetColors(float hue , float sat , float light , float alpha) {
      h = hue;
      s = sat;
      l = light;
      a = alpha;
      col = ::GetEagleColor(al_color_hsl(h,s,l));
      col.SetAlpha(a);
      buf_drawn = false;
   }
   
   float HuePick();
   float SatPick();
   
   EagleColor GetEagleColor();
   
   
};




#endif // ColorPicker_HPP
