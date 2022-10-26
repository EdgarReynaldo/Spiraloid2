


#include "Program.hpp"

#include "Eagle/StringWork.hpp"




int Program::Init() {
   
   if (!al_init()) {
      return 1;
   }
///   void al_register_assert_handler(void (*handler)(char const *expr,
///      char const *file, int line, char const *func))
   
   al_register_assert_handler(AllegroAssertHandler);
   
   if (!al_init_primitives_addon()) {
      return 2;
   }
   if (!al_init_image_addon()) {
      return 3;
   }
   if (!al_install_keyboard()) {
      return 4;
   }
   if (!al_install_mouse()) {
      return 5;
   }
   
   timer = al_create_timer(1.0/60.0);
   queue = al_create_event_queue();
   
   al_register_event_source(queue , al_get_timer_event_source(timer));
   al_register_event_source(queue , al_get_keyboard_event_source());
   al_register_event_source(queue , al_get_mouse_event_source());
   
   
   /// Setup monitor info and display modes
   monitor_info.RefreshMonitorInfo();
   
   Assert(monitor_info.NumMonitors() > 0);
   
   int adapter = monitor_info.GetAdapterNum(0);
   al_set_new_display_adapter(adapter);
   Monitor m;
   monitor_info.GetMonitorData(0 , &m);
   
   int fsw = m.w;
   int fsh = m.h;
   int ww = fsw/2;
   int wh = fsh/2;
   
///   int fsw = 1920;
///   int fsh = 1080;
///   int ww = 800;
///   int wh = 600;
   
   if (!display.Create(fullscreen , fsw , fsh , ww , wh)) {
      throw Exception(StringPrintF("Failed to create %d x %d %s.\n" ,
                                    fullscreen?fsw:ww , fullscreen?fsh:wh , fullscreen?"Fullscreen window":"Window"));
   }
   al_clear_to_color(al_map_rgb(255,255,255));
   display.Flip();
   
   al_register_event_source(queue , al_get_display_event_source(display));
   
   for (int i = 0 ; i < NUM_SCREENS ; ++i) {
      ProgramScreen* pscreen = screens[i];
      pscreen->SetKeyDownArray(keys_down);
      pscreen->Init();
   }

   spiraloid_screen.SetSpiraloidTransform(display.CX() , display.CY() , display.SX() , display.SY());
   
   return 0;
}
   
   
   
   
void Program::Run() {

   al_start_timer(timer);
   
   do {
      if (redraw) {
         
         display.DrawToBuffer();
         
         screens[active_screen]->Draw();
         
         display.Flip();
         
         redraw = false;
      }
      
      do {
         ALLEGRO_EVENT ev;
         al_wait_for_event(queue , &ev);

         if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            keys_down[ev.keyboard.keycode] = true;
         }
         if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            keys_down[ev.keyboard.keycode] = false;
         }
         if (ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {
            printf("ALLEGRO_EVENT_DISPLAY_RESIZE received.\n");
            display.AcknowledgeResize();
            spiraloid_screen.SetSpiraloidTransform(display.CX() , display.CY() , display.SX() , display.SY());
            redraw = true;
         }
         if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            quit = true;
         }
         if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
               quit = true;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_F) {
               fullscreen = !fullscreen;
               display.ToggleFullscreen();
               spiraloid_screen.SetSpiraloidTransform(display.CX() , display.CY() , display.SX() , display.SY());
               al_register_event_source(queue , al_get_display_event_source(display));
               redraw = true;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_S) {
               if (keys_down[ALLEGRO_KEY_LCTRL] || keys_down[ALLEGRO_KEY_RCTRL]) {
                  display.SaveScreenie();
               }
            }
         }
         
         ProgramScreen* screen = screens[active_screen];
         screen->HandleEvent(ev);
         if (screen->NeedsRedraw()) {
            redraw = true;
         }
         
         if (quit) {break;}

      } while (!al_is_event_queue_empty(queue));
      
   } while (!quit);
   
}



