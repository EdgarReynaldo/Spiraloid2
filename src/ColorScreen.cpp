



#include "ColorScreen.hpp"
#include "Spirals.hpp"



const unsigned int TOPIC_COLOR_WIDGET = NextFreeTopicId();



int ColorWidget::PrivateHandleEvent(EagleEvent ee) {
   if (ee.type == EAGLE_EVENT_MOUSE_BUTTON_DOWN) {
      if (InnerArea().Contains(ee.mouse.x , ee.mouse.y)) {
         QueueUserMessage(WidgetMsg(this , TOPIC_COLOR_WIDGET , COLOR_WIDGET_SELECTED));
         return DIALOG_TAKE_FOCUS;
      }
   }
   return DIALOG_OKAY;
}



int ColorWidget::PrivateCheckInputs() {
   bool color_changed = false;
   if ((int)Flags() & HASFOCUS) {
      if (input_key_held(EAGLE_KEY_ANY_SHIFT)) {
         if (input_key_held(EAGLE_KEY_R)) {
            r -= 1;
            color_changed = true;
         }
         if (input_key_held(EAGLE_KEY_G)) {
            g -= 1;
            color_changed = true;
         }
         if (input_key_held(EAGLE_KEY_B)) {
            b -= 1;
            color_changed = true;
         }
         if (input_key_held(EAGLE_KEY_A)) {
            a -= 1;
            color_changed = true;
         }
      }
      else {
         if (input_key_held(EAGLE_KEY_R)) {
            r += 1;
            color_changed = true;
         }
         if (input_key_held(EAGLE_KEY_G)) {
            g += 1;
            color_changed = true;
         }
         if (input_key_held(EAGLE_KEY_B)) {
            b += 1;
            color_changed = true;
         }
         if (input_key_held(EAGLE_KEY_A)) {
            a += 1;
            color_changed = true;
         }
      }
      if (color_changed) {
         SetRedrawFlag();
         QueueUserMessage(WidgetMsg(this , TOPIC_COLOR_WIDGET , COLOR_WIDGET_CHANGED));
         return DIALOG_INPUT_USED;
      }
   }
   return DIALOG_OKAY;
}



int ColorWidget::PrivateUpdate(double dt) {
   (void)dt;
   return DIALOG_OKAY;
}



void ColorWidget::PrivateDisplay(EagleGraphicsContext* win , int xpos , int ypos) {
   win->DrawFilledRectangle(InnerArea().MovedBy(Pos2I(xpos,ypos)) , EagleColor((int)r , (int)g , (int)b , (int)a));
}



ColorWidget::ColorWidget() :
      WidgetBase("ColorWidget" , "Color square"),
      r(),
      g(),
      b(),
      a()
{
   r.SetValues(0 , 0 , 255 , 0 , false);
   g.SetValues(0 , 0 , 255 , 0 , false);
   b.SetValues(0 , 0 , 255 , 0 , false);
   a.SetValues(0 , 0 , 255 , 0 , false);
}



ALLEGRO_COLOR ColorWidget::AllegroColor() {
   return al_map_rgba((int)r , (int)g , (int)b , (int)a);
}



void ColorWidget::SetColors(int rcol , int gcol , int bcol , int acol) {
   r = rcol;
   g = gcol;
   b = bcol;
   a = acol;
   SetRedrawFlag();
}



/// -------------------------------------      ShadeWidget    ------------------------------------------



int ShadeWidget::PrivateHandleEvent(EagleEvent ee) {
   (void)ee;
   return DIALOG_OKAY;
}



int ShadeWidget::PrivateCheckInputs() {
   return DIALOG_OKAY;
}



int ShadeWidget::PrivateUpdate(double dt) {
   (void)dt;
   return DIALOG_OKAY;
}



void ShadeWidget::PrivateDisplay(EagleGraphicsContext* win , int xpos , int ypos) {
   if (!cset) {return;}
   int nshades = (int)cset->NumColors()*(int)cset->NumShades();
   int nlines = nshades/InnerArea().W() + ((nshades % InnerArea().W())?1:0);
   int height = InnerArea().H()/nlines;
   int x = InnerArea().X();
   int y = InnerArea().Y();
   cset->ResetColorIndex();
   for (int i = 0 ; i < nshades ; ++i) {
      win->DrawLine(x + xpos , y + ypos , x + xpos , y + ypos + height - 1 , 1.0 , GetEagleColor(cset->GetNextColor()));
      ++x;
      if (x >= InnerArea().BRX()) {
         x = InnerArea().X();
         y += height;
      }
   }
}



ShadeWidget::ShadeWidget(Colorset* pcolorset) :
      WidgetBase("Shadewidget" , "Color line"),
      cset(pcolorset)
{}



void ShadeWidget::SetColorset(Colorset* pcset) {
   EAGLE_ASSERT(pcset);
   cset = pcset;
   SetBgRedrawFlag();
}



/// ---------------------------------------      ColorScreen     -----------------------------------------



void ColorScreen::HandleWidgetEvent(WidgetMsg wmsg) {
   

   bool cpicker_changed = false;
   bool slider_changed = false;
   bool color_changed = false;
   bool color_selected = false;
   
   bool rgba_changed = false;
   bool hsl_changed = false;

   if (wmsg.from == &cpicker) {
      cpicker_changed = true;
      hsl_changed = true;
   }
   if (wmsg.from == &bgcolwidget) {
      if ((wmsg.msgs == COLOR_WIDGET_SELECTED) || (wmsg.msgs == COLOR_WIDGET_CHANGED)) {
         selected_color = -1;
         ALLEGRO_COLOR c = bgcolwidget.AllegroColor();
         unsigned char r,g,b,a;
         al_unmap_rgba(c , &r , &g , &b , &a);
         float h,s,l;
         al_color_rgb_to_hsl(r/255.0f , g/255.0f , b/255.0f , &h , &s , &l);
         rsl.SetPercent(r/255.0f);
         gsl.SetPercent(g/255.0f);
         bsl.SetPercent(b/255.0f);
         asl.SetPercent(a/255.0f);
         hsl.SetPercent(h/360.0f);
         ssl.SetPercent(s);
         lsl.SetPercent(l);
         cpicker.SetColors(h,s,l,a/255.0f);
         spiraloid->bg_red   = r;
         spiraloid->bg_green = g;
         spiraloid->bg_blue  = b;
         
      }
   }
   
   for (unsigned int i = 0 ; i < 12 ; ++i) {
         
      if (wmsg.from == &colwidgets[i]) {
         if ((wmsg.msgs == COLOR_WIDGET_SELECTED) || (wmsg.msgs == COLOR_WIDGET_CHANGED)) {
            selected_color = i;
            ALLEGRO_COLOR c = colwidgets[i].AllegroColor();
            unsigned char r,g,b,a;
            al_unmap_rgba(c , &r , &g , &b , &a);
            float h,s,l;
            al_color_rgb_to_hsl(r/255.0f , g/255.0f , b/255.0f , &h , &s , &l);
            rsl.SetPercent(r/255.0f , false);
            gsl.SetPercent(g/255.0f , false);
            bsl.SetPercent(b/255.0f , false);
            asl.SetPercent(a/255.0f , false);
            hsl.SetPercent(h/360.0f , false);
            ssl.SetPercent(s , false);
            lsl.SetPercent(l , false);
            cpicker.SetColors(h,s,l,a/255.0f);
            cset.Color(i) = c;
         }
      }
   }

   if (wmsg.from == &cpicker) {
      hsl_changed = true;
      hsl.SetPercent(cpicker.HuePick());
      ssl.SetPercent(cpicker.SatPick());
   }
   
   
   Slider* const sliders[7] = { &rsl,
                                &gsl,
                                &bsl,
                                &asl,
                                &hsl,
                                &ssl,
                                &lsl };
   for (unsigned int i = 0 ; i < 4 ; ++i) {
      if (wmsg.from == sliders[i]) {
         rgba_changed = true;
      }
   }
   for (unsigned int i = 4 ; i < 7 ; ++i) {
      if (wmsg.from == sliders[i]) {
         hsl_changed = true;
      }
   }

   if (rgba_changed) {
      float hue,sat,light;
      
      al_color_rgb_to_hsl(rsl.GetActual() , gsl.GetActual() , bsl.GetActual() , &hue , &sat , &light);

      hsl.SetPercent(hue/360.0 , false);
      ssl.SetPercent(sat , false);
      lsl.SetPercent(light , false);
      
      if (selected_color != -1) {
         cset.Color(selected_color) = al_map_rgba_f(rsl.GetActual() , gsl.GetActual() , bsl.GetActual() , asl.GetActual());
      }
      else {
         spiraloid->bg_red   = (int)(rsl.GetActual()*255.0f);
         spiraloid->bg_green = (int)(gsl.GetActual()*255.0f);
         spiraloid->bg_blue  = (int)(bsl.GetActual()*255.0f);
      }
   }
   else if (hsl_changed) {

      float r,g,b;
      
      al_color_hsl_to_rgb(hsl.GetActual()*360.0f , ssl.GetActual() , lsl.GetActual() , &r , &g , &b);
   
      rsl.SetPercent(r , false);
      gsl.SetPercent(g , false);
      bsl.SetPercent(b , false);
      
      if (selected_color != -1) {
         cset.Color(selected_color) = al_map_rgba_f(r , g , b , asl.GetActual());
      }
      else {
         spiraloid->bg_red   = (int)(r*255.0f);
         spiraloid->bg_green = (int)(g*255.0f);
         spiraloid->bg_blue  = (int)(b*255.0f);
      }
   }
}



void ColorScreen::RespondToEvent(EagleEvent e , EagleThread* thread) {
   (void)e;
   (void)thread;
}


#include "Spirals.hpp"



ColorScreen::ColorScreen(Spiraloid* pspiraloid , EagleGraphicsContext* window) :
      ProgramScreen(),
      EagleEventListener(),
      win(window),
      font(0),
      original_cset(0),
      cset(),
      spiraloid(pspiraloid),
      gui(win , "WidgetHandler" , "ColorGUI"),
      rlayout("RelativeLayout" , "Color Picker Layout"),
      gridlayout(4 , 3 , "GridLayout" , "Color grid"),
      tablelayout("Color table"),
      colwidgets(),
      bgcolwidget(),
      shadewidget(&cset),
      cpicker(win),
      rsl("RSL" , "Red slider"        , true , true),
      gsl("GSL" , "Green slider"      , true , true),
      bsl("BSL" , "Blue slider"       , true , true),
      asl("ASL" , "Alpha slider"      , true , true),
      hsl("HSL" , "Hue slider"        , true , true),
      ssl("SSL" , "Saturation slider" , true , true),
      lsl("LSL" , "Lightness slider"  , true , true),
      clabels(),
      vlabels(),
      nctext(),
      nstext(),
      selected_color(-1)
{
   EAGLE_ASSERT(spiraloid);
   original_cset = &(spiraloid->colorset);
   font = window->LoadFont("Verdana.ttf" , -16);
   EAGLE_ASSERT(font && font->Valid());
}



ColorScreen::~ColorScreen() {
   EAGLE_ASSERT(win);
   if (font) {
      win->FreeFont(font);
      font = 0;
   }
}



bool ColorScreen::Init() {

   if (original_cset) {
      cset = *original_cset;
      cset.Refresh();
   }

///   cset.PrintColors2();
   
   for (unsigned int i = 0 ; i < 12 ; ++i) {
      unsigned char r,g,b,a;
      al_unmap_rgba(cset.GetMainColor(i) , &r , &g , &b , &a);
      colwidgets[i].SetColors(r,g,b,a);
   }

   bgcolwidget.SetZOrder(bgcolwidget.ZValue() - 1);
   bgcolwidget.SetColors(spiraloid->bg_red , spiraloid->bg_green , spiraloid->bg_blue , 255);

   shadewidget.SetColorset(&cset);/// Use the copy
   
   if (!gui.SetupBuffer(win->Width() , win->Height() , win)) {
      return false;
   }
   gui.SetBackgroundColor(EagleColor(0 , 127 , 64 , 255));
   gui.SetWidgetArea(WIDGETAREA(Rectangle(0 , 0 , win->Width() , win->Height()) , BOXAREA(2) , BOXAREA(2) , BOXAREA(2)));
   gui.SetRootLayout(&rlayout);
   
   /// Relative Layout

   nctext.SetupText(StringPrintF("NC %d" , (int)cset.NumColors()) , font , HALIGN_CENTER , VALIGN_CENTER);
   nstext.SetupText(StringPrintF("NS %d" , (int)cset.NumShades()) , font , HALIGN_CENTER , VALIGN_CENTER);

   rlayout.Resize(7);
   rlayout.PlaceWidget(&gridlayout   , 0 , LayoutRectangle(0.0 , 0.0  , 1.0 , 0.35));
   rlayout.PlaceWidget(&bgcolwidget  , 1 , LayoutRectangle(0.0 , 0.0  , 1.0 , 0.35));

   rlayout.PlaceWidget(&tablelayout  , 2 , LayoutRectangle(0.0 , 0.5  , 0.5 , 0.5));
   rlayout.PlaceWidget(&shadewidget  , 3 , LayoutRectangle(0.0 , 0.35 , 0.9 , 0.15));
   EagleInfo() << shadewidget.GetWidgetArea() << std::endl;
   
   rlayout.PlaceWidget(&nctext       , 4 , LayoutRectangle(0.9 , 0.35  , 0.1 , 0.075));
   rlayout.PlaceWidget(&nstext       , 5 , LayoutRectangle(0.9 , 0.425 , 0.1 , 0.075));
   
   rlayout.PlaceWidget(&cpicker      , 6 , LayoutRectangle(0.5 , 0.5  , 0.5 , 0.5));
   /// Grid Layout

   gridlayout.SetGlobalPadding(2,2);
   gridlayout.SetGlobalSpacing(5,5);
   gridlayout.ResizeGrid(4 , 3);
   for (unsigned int i = 0 ; i < 12 ; ++i) {
//      int y = i/4;
//      int x = i%4;
      gridlayout.PlaceWidget(&colwidgets[i] , i);
   }

   
   /// Table Layout
   
   tablelayout.SetPadding(2);
   
   const float cw = 1.0f/7.0f;
   tablelayout.Resize(std::vector<float>({cw , cw , cw , cw , cw , cw , cw}) , std::vector<float>({0.7f , 0.15f , 0.15f}));
   
   Slider* const sliders[7] = {&rsl , &gsl , &bsl , &asl , &hsl , &ssl , &lsl};

   static const std::string labeltext[7] = {"R" , "G" , "B" , "A" , "H" , "S" , "L"};
   static const double sliderpercent[7] = {0.0 , 0.0 , 0.0 , 1.0 , 0.0 , 0.0 , 0.0};
   static const std::string start_values[7] = {"0" , "0" , "0" , "255" , "0.0" , "0.0" , "0.0"};

   for (unsigned int i = 0 ; i < 7 ; ++i) {
      sliders[i]->SetPercent(sliderpercent[i] , false);
      clabels[i].SetupText(labeltext[i] , font , HALIGN_CENTER , VALIGN_CENTER);
      vlabels[i].SetupText(start_values[i] , font , HALIGN_CENTER , VALIGN_CENTER);
      tablelayout.PlaceWidget(sliders[i] , i);
      tablelayout.PlaceWidget(&clabels[i] , i + 7);
      tablelayout.PlaceWidget(&vlabels[i] , i + 14);
   }
   
   return true;
}



bool ColorScreen::HandleEvent(EagleEvent ev) {
   
   if (ev.type == EAGLE_EVENT_KEY_CHAR) {
      if (ev.keyboard.keycode == EAGLE_KEY_UP) {
         ++(cset.NumShades());
         cset.Refresh();
         nstext.SetupText(StringPrintF("NS %d" , (int)cset.NumShades()) , font);
         shadewidget.SetBgRedrawFlag();
      }
      else if (ev.keyboard.keycode == EAGLE_KEY_DOWN) {
         --(cset.NumShades());
         cset.Refresh();
         nstext.SetupText(StringPrintF("NS %d" , (int)cset.NumShades()) , font);
         shadewidget.SetBgRedrawFlag();
      }
   }

   int GUISTATUS = gui.HandleEvent(ev);

   while (gui.HasMessages()) {
      HandleWidgetEvent(gui.TakeNextMessage());
   }
   
   return GUISTATUS;
//   return DIALOG_OKAY;
}



void ColorScreen::Update(double dt) {
   gui.Update(dt);
//   return DIALOG_OKAY;
}



void ColorScreen::Draw(EagleGraphicsContext* win) {
   gui.Display(win , 0 , 0);
}



bool ColorScreen::NeedsRedraw() {
   return true;
   return (int)gui.Flags() & NEEDS_REDRAW;
}



void ColorScreen::ResetScreen() {
   gui.ClearLayout();
   (void)Init();
}

