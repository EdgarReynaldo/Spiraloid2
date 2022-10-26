


#include "Program.hpp"

#include "Eagle/StringWork.hpp"




NewProgram::NewProgram() :
      sys(0),
      win(0),
      config(),
      minfo(),
      display(),
      spiraloid_screen(0),
      screens(),
      active_screen(0),
      fullscreen(false),
      redraw(true),
      quit(false)
      
{
   screens[0] = &spiraloid_screen;
}



bool NewProgram::Init() {
   sys = GetAllegro5System();
   
   EAGLE_ASSERT(sys);
   
   int sysret = sys->Initialize(EAGLE_FULL_SETUP);
   
   EAGLE_ASSERT(sysret & EAGLE_STANDARD_SETUP);
   
   gconfig = &config;
   
   if (!config.Setup("Graphics.cfg")) {
      EagleError() << "Failed to setup spiraloid config!" << std::endl;
      return false;
   }
   
   minfo.RefreshMonitorInfo();
   EAGLE_ASSERT(minfo.NumMonitors() > 0);
   
   bool d = display.Create(sys , config.Fullscreen() , config.FSWidth() , config.FSHeight() , config.WWidth() , config.WHeight() , EAGLE_OPENGL);
   if (!d) {
      EagleCritical() << "Failed to create spiraloid display!" << std::endl;
   }
   
   win = display.GetDisplay();
   win->Clear(EagleColor(255,255,255));
   win->FlipDisplay();
   
}
   for (int i = 0 ; i < NUM_SCREENS ; ++i) {
      ProgramScreen* pscreen = screens[i];
      pscreen->Init();
   }
   screens[0] = &spiraloid_screen;
   
   
   spiraloid_screen.SetSpiraloidTransform(display.CX() , display.CY() , display.SX() , display.SY());
   
   return 0;
}
   
   
   
   
void NewProgram::Run() {

   sys->GetSystemTimer()->Start();

   do {
      if (redraw) {
         
         display.DrawToBuffer();
         
         screens[active_screen]->Draw(win);
         
         display.Flip();
         
         redraw = false;
      }
      
      do {
         EagleEvent ev;
         ev = sys->WaitForSystemEventAndUpdateState();

         if (ev.type == EAGLE_EVENT_DISPLAY_RESIZE) {
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
            if (ev.keyboard.keycode == EAGLE_KEY_F) {
               fullscreen = !fullscreen;
               display.ToggleFullscreen();
               spiraloid_screen.SetSpiraloidTransform(display.CX() , display.CY() , display.SX() , display.SY());
               redraw = true;
            }
            if (ev.keyboard.keycode == EAGLE_KEY_S) {
               if (input_key_held(EAGLE_KEY_LCTRL) || input_key_held(EAGLE_KEY_RCTRL)) {
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

      } while (!sys->UpToDate());
      
   } while (!quit);
   
}



