



#ifndef ColorScreen_HPP
#define ColorScreen_HPP

#include "Colors.hpp"
#include "Values.hpp"
#include "ProgramScreen.hpp"
#include "TableLayout.hpp"
#include "Eagle.hpp"
#include "ColorPicker.hpp"



extern const unsigned int TOPIC_COLOR_WIDGET;


enum COLOR_WIDGET_MSGS {
   COLOR_WIDGET_CHANGED = 0,
   COLOR_WIDGET_SELECTED = 1
};




class ColorWidget : public WidgetBase {

   Value r,g,b,a;
   
   




   /// Private interface, override to define behavior
   virtual int PrivateHandleEvent(EagleEvent ee);
   virtual int PrivateCheckInputs();
   virtual int PrivateUpdate(double dt);
   virtual void PrivateDisplay(EagleGraphicsContext* win , int xpos , int ypos);


   /// Callbacks, override and/or call if you need to
//   virtual void OnAreaChanged();
//   virtual void OnAttributeChanged(const ATTRIBUTE& a , const VALUE& v);
//   virtual void OnFlagChanged(WIDGET_FLAGS f , bool on);
//   virtual void OnColorChanged();


public :
   
   ColorWidget();
   
   
   ALLEGRO_COLOR AllegroColor();
   void SetColors(int rcol , int gcol , int bcol , int acol);
};



class ShadeWidget : public WidgetBase {
   Colorset* cset;
   
   /// Private interface, override to define behavior
   virtual int PrivateHandleEvent(EagleEvent ee);
   virtual int PrivateCheckInputs();
   virtual int PrivateUpdate(double dt);
   virtual void PrivateDisplay(EagleGraphicsContext* win , int xpos , int ypos);

public :
   ShadeWidget(Colorset* pcolorset);
   
   void SetColorset(Colorset* pcset);
};


class Spiraloid;

class ColorScreen : public ProgramScreen , public EagleEventListener {
   
   EagleGraphicsContext* win;
   EagleFont* font;
   
   Colorset* original_cset;
   Colorset cset;
   
   Spiraloid* spiraloid;
   
   WidgetHandler gui;
   RelativeLayout rlayout;
   GridLayout gridlayout;
   SimpleTable tablelayout;
   ColorWidget colwidgets[12];
   ColorWidget bgcolwidget;
   ShadeWidget shadewidget;
   ColorPicker cpicker;
   Slider rsl,gsl,bsl,asl,hsl,ssl,lsl;
   BasicText clabels[7];
   BasicText vlabels[7];
   
   BasicText nctext;
   BasicText nstext;
   
   int selected_color;
   
   
   void HandleWidgetEvent(WidgetMsg wmsg);
   
   virtual void RespondToEvent(EagleEvent e , EagleThread* thread = MAIN_THREAD);
   


public :
   
   ColorScreen(Spiraloid* pspiraloid , EagleGraphicsContext* window);
   ~ColorScreen();
   virtual bool Init();
   bool Valid();
   
   virtual bool HandleEvent(EagleEvent ev);
   virtual void Update(double dt);
   virtual void Draw(EagleGraphicsContext* win);
   
   virtual bool NeedsRedraw();
   virtual void ResetScreen();

};




#endif // ColorScreen_HPP
