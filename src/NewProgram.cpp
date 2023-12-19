


#include "NewProgram.hpp"

#include "Eagle/StringWork.hpp"
#include "Eagle/backends/Allegro5/Allegro5System.hpp"
#include "Eagle.hpp"
#include "Eagle/backends/Allegro5/Allegro5FileSystem.hpp"



#include <sstream>


void AllegroLogHandler(const char* text) {
   EagleInfo() << text << std::endl;
}


NewProgram::NewProgram() :
      sys(0),
      win(0),
      config(),
      minfo(),
      display(),
      spiraloid_screen(),
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

   al_register_trace_handler(AllegroLogHandler);

   GraphicsHardware* hw = sys->GetGraphicsHardware();
   
   EagleInfo() << "Graphics Hardware reports " << hw->NumAdapters(GRAPHICS_OPENGL) << " adapters." << std::endl;

   if (!config.Setup("Graphics.cfg")) {
      EagleError() << "Failed to setup spiraloid config!" << std::endl;
      return false;
   }



   std::stringstream eagle_info;
   EagleInfo() << std::endl;
   std::vector<std::string> pvec = GetAbsolutePath("Graphics.cfg");
   for (unsigned int i = 0 ; i < pvec.size() ; ++i) {
      eagle_info << i << "# " << pvec[i] << std::endl;
      EagleInfo() << eagle_info.str() << std::endl;
      eagle_info.str("");
   }
   pvec = GetAbsolutePath("e:/usr64/projects/Spiraloid2/Graphics.cfg");
   for (unsigned int i = 0 ; i < pvec.size() ; ++i) {
      eagle_info << i << "# " << pvec[i] << std::endl;
      EagleInfo() << eagle_info.str() << std::endl;
      eagle_info.str("");
   }
   
   pvec = GetAbsolutePath("e:\\usr64\\projects\\Spiraloid2\\Graphics.cfg");
   for (unsigned int i = 0 ; i < pvec.size() ; ++i) {
      eagle_info << i << "# " << pvec[i] << std::endl;
      EagleInfo() << eagle_info.str() << std::endl;
      eagle_info.str("");
   }

   FilePath fp("Graphics.cfg");
   EagleInfo() << fp.Path() << std::endl;
   
   fp = FilePath("e:/usr64/projects/Spiraloid2/Graphics.cfg");
   EagleInfo() << fp.Path() << std::endl;
   
   fp = FilePath("e:\\usr64\\projects\\Spiraloid2\\Graphics.cfg");
   EagleInfo() << fp.Path() << std::endl;

   FSInfo info1(FilePath("Graphics.cfg"));
   FSInfo info2(FilePath("e:\\usr64\\projects\\Spiraloid2\\Graphics.cfg"));
   FSInfo info3(FilePath("e:/usr64/projects/Spiraloid2/Graphics.cfg"));

   std::string path = info2.Path();/// e:/usr64/projects/Spiraloid2/Graphics.cfg
   ALLEGRO_FS_ENTRY* fs = al_create_fs_entry(path.c_str());
   FSInfo info;
   if (al_fs_entry_exists(fs)) {
      info = GetFSInfo(fs);
   }
   al_destroy_fs_entry(fs);






   EagleInfo() << info1.Path() << std::endl;
   EagleInfo() << info2.Path() << std::endl;
   EagleInfo() << info3.Path() << std::endl;
   
   FSInfo fsinfo = sys->GetFileSystem()->GetFileInfo(FilePath("Graphics.cfg"));
   EagleInfo() << fsinfo.Path() << std::endl;
   
   fsinfo = sys->GetFileSystem()->GetFileInfo(FilePath("e:/usr64/projects/Spiraloid2/Graphics.cfg"));
   EagleInfo() << fsinfo.Path() << std::endl;
   
   fsinfo = sys->GetFileSystem()->GetFileInfo(FilePath("e:\\usr64\\projects\\Spiraloid2\\Graphics.cfg"));
   EagleInfo() << fsinfo.Path() << std::endl;
   
   
   
   minfo.RefreshMonitorInfo();
//br   EAGLE_ASSERT(minfo.NumMonitors() > 0);
   
   bool d = display.Create(sys , config.Fullscreen() , config.FSWidth() , config.FSHeight() , config.WWidth() , config.WHeight() , EAGLE_OPENGL);
   if (!d) {
      EagleCritical() << "Failed to create spiraloid display!" << std::endl;
   }
   



   win = display.GetDisplay();
   win->Clear(EagleColor(255,255,255));
   win->FlipDisplay();

   for (int i = 0 ; i < NUM_SCREENS ; ++i) {
      ProgramScreen* pscreen = screens[i];
      pscreen->Init();
   }
   screens[0] = &spiraloid_screen;
   
   
   spiraloid_screen.SetSpiraloidTransform(display.CX() , display.CY() , display.SX() , display.SY());
   
   return 0;
}
   
   
   
   
int NewProgram::Run() {

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
   return 0;
}



