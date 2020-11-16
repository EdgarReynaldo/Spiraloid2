


#include "Program.hpp"

#include "Eagle/StringWork.hpp"




Program::Program() :
      a5sys(GetAllegro5System()),
      win(0),
      timer(0),
      queue(0),
//         buffer(0),
      monitor_info(),
      adapter(-1),
      display(a5sys),
      fullscreen(false),
      redraw(true),
      quit(false),
      init_state(-1),
      spiraloid_screen(0),
      color_screen(0),
      screens(),
      active_screen(-1)
{
   init_state = Init();
}



Program::~Program() {
   for (int i = 0 ; i < NUM_SCREENS ; ++i) {
      if (screens[i]) {
         ProgramScreen* pscreen = screens[i];
         delete pscreen;
         screens[i] = 0;
      }
   }
}



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
   
   bool disp = display.Create(fullscreen , fsw , fsh , ww , wh);
   if (!disp) {
      throw EagleException(StringPrintF("Failed to create %d x %d %s.\n" ,
                                    fullscreen?fsw:ww , fullscreen?fsh:wh , fullscreen?"Fullscreen window":"Window"));
   }
   win = display.GetWindow();
//   al_clear_to_color(al_map_rgb(255,255,255));
//   display.Flip();
   
   spiraloid_screen = new SpiraloidScreen();
   if (!spiraloid_screen->Init()) {
      throw EagleException("Failed to initialize spiraloid screen.");
   }


   color_screen = new ColorScreen(spiraloid_screen->GetSpiraloid() , win);
   if (!color_screen->Init()) {
      delete spiraloid_screen;
      throw EagleException("Failed to initialize color screen.");
   }

   screens[0] = spiraloid_screen;
   screens[1] = color_screen;
   active_screen = 0;
   
   spiraloid_screen->SetSpiraloidTransform(display.CX() , display.CY() , display.SX() , display.SY());
   spiraloid_screen->SetRefresh(timer->SPT());
   return 0;
}
   
   
   
   
void Program::Run() {

   timer->Start();
   
   
   active_screen = 1;
   
   do {
      if (redraw) {
         display.DrawToBuffer();
         screens[active_screen]->Draw(win);
         display.Flip();
         redraw = false;
      }
      
      do {
         EagleEvent ev = a5sys->WaitForSystemEventAndUpdateState();

         if (ev.type == EAGLE_EVENT_DISPLAY_RESIZE) {
            printf("EAGLE_EVENT_DISPLAY_RESIZE received.\n");
            display.AcknowledgeResize();
            spiraloid_screen->SetSpiraloidTransform(display.CX() , display.CY() , display.SX() , display.SY());
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
               spiraloid_screen->SetSpiraloidTransform(display.CX() , display.CY() , display.SX() , display.SY());
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



