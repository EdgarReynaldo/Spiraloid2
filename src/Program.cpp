


#include "Program.hpp"

#include "Eagle/StringWork.hpp"




int Program::Init() {
   
   a5sys = GetAllegro5System();
   EAGLE_ASSERT(a5sys);
   
   int ret = a5sys->Initialize(EAGLE_FULL_SETUP);
   if (EAGLE_FULL_SETUP != ret) {
      EagleLog() << "Failed to initialize some system components. Continuing." << std::endl;
   }
   
   timer = a5sys->GetSystemTimer();
   queue = a5sys->GetSystemQueue();
   
   
   /// Setup monitor info and display modes
   monitor_info.RefreshMonitorInfo();
   
   EAGLE_ASSERT(monitor_info.NumMonitors() > 0);
   
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
      throw EagleException(StringPrintF("Failed to create %d x %d %s.\n" ,
                                    fullscreen?fsw:ww , fullscreen?fsh:wh , fullscreen?"Fullscreen window":"Window"));
   }
   al_clear_to_color(al_map_rgb(255,255,255));
   display.Flip();
   
   for (int i = 0 ; i < NUM_SCREENS ; ++i) {
      ProgramScreen* pscreen = screens[i];
      pscreen->Init();
   }

   spiraloid_screen.SetSpiraloidTransform(display.CX() , display.CY() , display.SX() , display.SY());
   spiraloid_screen.SetRefresh(timer->SPT());
   return 0;
}
   
   
   
   
void Program::Run() {

   timer->Start();
   
   do {
      if (redraw) {
         display.DrawToBuffer();
         screens[active_screen]->Draw();
         display.Flip();
         redraw = false;
      }
      
      do {
         EagleEvent ev = a5sys->WaitForSystemEventAndUpdateState();

         if (ev.type == EAGLE_EVENT_DISPLAY_RESIZE) {
            printf("EAGLE_EVENT_DISPLAY_RESIZE received.\n");
            display.AcknowledgeResize();
            spiraloid_screen.SetSpiraloidTransform(display.CX() , display.CY() , display.SX() , display.SY());
            redraw = true;
         }
         if (ev.type == EAGLE_EVENT_DISPLAY_CLOSE) {
            quit = true;
         }
         if (ev.type == EAGLE_EVENT_KEY_DOWN) {
            if (ev.keyboard.keycode == EAGLE_KEY_ESCAPE) {
               quit = true;
            }
            if (ev.keyboard.keycode == EAGLE_KEY_F && input_key_held(EAGLE_KEY_ANY_SHIFT)) {
               fullscreen = !fullscreen;
               display.ToggleFullscreen();
               spiraloid_screen.SetSpiraloidTransform(display.CX() , display.CY() , display.SX() , display.SY());
               redraw = true;
            }
            if (ev.keyboard.keycode == EAGLE_KEY_S) {
               if (keydown[EAGLE_KEY_LCTRL] || keydown[EAGLE_KEY_RCTRL]) {
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

      } while (!a5sys->UpToDate());
      
   } while (!quit);
   
}



