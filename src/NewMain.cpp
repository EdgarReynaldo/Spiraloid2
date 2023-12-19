


#include "NewProgram.hpp"
#include "Monitors.hpp"

#include "Eagle/Logging.hpp"
#include "Eagle/backends/Allegro5Backend.hpp"


#include <allegro5/allegro_windows.h>
#include <windows.h>
#include <allegro5/allegro_direct3d.h>

 void DumpDevice(const DISPLAY_DEVICE& dd, int nSpaceCount )
 {
     printf("%*sDevice Name: %s\n", nSpaceCount, "", dd.DeviceName );
     printf("%*sDevice String: %s\n", nSpaceCount, "", dd.DeviceString );
     printf("%*sState Flags: %x\n", nSpaceCount, "", dd.StateFlags );
     printf("%*sDeviceID: %s\n", nSpaceCount, "", dd.DeviceID );
     printf("%*sDeviceKey: ...%s\n\n", nSpaceCount, "", dd.DeviceKey+42 );
 }


int main(int argc , char** argv) {
   
   (void)argc;
   (void)argv;
   
   SendOutputToFile("Log.txt" , "NVA" , false);
   

   Allegro5System* sys = GetAllegro5System();
   if (!sys->Initialize(EAGLE_FULL_SETUP)) {
      EagleWarn() << "Failed some likely (non critical) subsystem" << std::endl;
   }
   
/**
   DISPLAY_DEVICE dd = {0};
   int count = 0;
   int c = 0;

   memset(&dd, 0, sizeof(dd));
   dd.cb = sizeof(dd);

   while (EnumDisplayDevices(NULL, count, &dd, 0) != false) {
      if (dd.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP)
         c++;
      count++;
   }

   EagleInfo() << "Win32 reports " << c << " monitors." << std::endl;
      
     dd = {0};
     
     dd.cb = sizeof(DISPLAY_DEVICE);//
    
     DWORD deviceNum = 0;
     while( EnumDisplayDevices(NULL, deviceNum, &dd, 0) ){
         DumpDevice( dd, 0 );
         DISPLAY_DEVICE newdd = {0};
         newdd.cb = sizeof(DISPLAY_DEVICE);
         DWORD monitorNum = 0;
         while ( EnumDisplayDevices(dd.DeviceName, monitorNum, &newdd, 0))
         {
             DumpDevice( newdd, 4 );
             monitorNum++;
         }
         puts("");
         deviceNum++;
     }
*/   
   
   
//   MonitorInfo minfo;
//   minfo.RefreshMonitorInfo();
//   EagleInfo() << "Minfo reports " << minfo.NumMonitors() << " monitors." << std::endl;
//   EAGLE_ASSERT(minfo.NumMonitors() > 0);
   NewProgram proggie;
   
   bool init = proggie.Init();
   
   if (!init) {
      EagleCritical() << "Failed to initialize spiraloid program. Halting." << std::endl;
      return 1;
   }
   
   return proggie.Run();
}














