



#ifndef Monitor_HPP
#define Monitor_HPP


#include "allegro5/allegro.h"

#include <vector>
using std::vector;



int CompareDisplayModes(const void* mode1 , const void* mode2);

int CompareMonitors(const void* minfo1 , const void* minfo2);







/**   
typedef struct ALLEGRO_DISPLAY_MODE {
   int width;          // Screen width
   int height;         // Screen height
   int format;         // The pixel format of the mode
   int refresh_rate;   // The refresh rate of the mode
} ALLEGRO_DISPLAY_MODE;
ALLEGRO_DISPLAY_MODE *al_get_display_mode(int index, ALLEGRO_DISPLAY_MODE *mode)   
int al_get_num_display_modes(void)   
//*/



class DisplayModes {

private :
   vector<ALLEGRO_DISPLAY_MODE> mode_list;
   
   void SortModes();
   
public :
///   DisplayModes();
   DisplayModes() :
         mode_list()
   {}
   
   void RefreshModes();
   
   ALLEGRO_DISPLAY_MODE GetMode(int mode_num) {return mode_list[mode_num];}
   
   int NumModes() {return mode_list.size();}
};



typedef struct Monitor {
public :
   int monitor_num;
   ALLEGRO_MONITOR_INFO info;
   DisplayModes modes;

   int area;
   int w;
   int h;
   
   void SetInfo(int monitor_number , ALLEGRO_MONITOR_INFO monitor_info);
} Monitor;




class MonitorInfo {
   
private :
   vector<Monitor> monitors;
   
public :
   MonitorInfo();
   
   
   void RefreshMonitorInfo();
   
   bool GetMonitorData(int monitor_num , Monitor* pmonitor);
   int  GetMonitorWidth(int monitor_num);
   int  GetMonitorHeight(int monitor_num);
   int  GetMonitorArea(int monitor_num);
   int  GetAdapterNum(int monitor_num);
   bool GetMonitorModes(int monitor_num , DisplayModes* pmodes);
   
   int NumMonitors() {return monitors.size();}
};




#endif // Monitor_HPP

