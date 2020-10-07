



#include "Monitors.hpp"





int CompareDisplayModes(const void* mode1 , const void* mode2) {
   ALLEGRO_DISPLAY_MODE* m1 = (ALLEGRO_DISPLAY_MODE*)mode1;
   ALLEGRO_DISPLAY_MODE* m2 = (ALLEGRO_DISPLAY_MODE*)mode2;
   int a1 = m1->width*m1->height;
   int a2 = m2->width*m2->height;
   int w1 = m1->width;
   int h1 = m1->height;
   int w2 = m2->width;
   int h2 = m2->height;
   double aspect1 = (double)w1/h1;
   double aspect2 = (double)w2/h2;
   
///   int f1 = m1->format;
///   int f2 = m2->format;

   int rr1 = m1->refresh_rate;
   int rr2 = m2->refresh_rate;

/**
int compar (const void* p1, const void* p2);

Taking two pointers as arguments (both converted to const void*). The function defines the order of the elements by returning (in a stable and transitive manner):
return value	meaning
<0	The element pointed to by p1 goes before the element pointed to by p2
0	The element pointed to by p1 is equivalent to the element pointed to by p2
>0	The element pointed to by p1 goes after the element pointed to by p2

//*/
      
   if (a1 > a2) {
      return -1;
   }
   if (aspect1 > aspect2) {
      return -1;
   }
   if (w1 > w2) {
      return -1;
   }
   if (h1 > h2) {
      return -1;
   }
   if (rr1 > rr2) {
      return -1;
   }
   
   if (a1 == a2 && aspect1 == aspect2 && w1 == w2 && h1 == h2 && rr1 == rr2) {return 0;}/// We don't care about formats really
   
   return 1;
}



int CompareMonitors(const void* minfo1 , const void* minfo2) {
   
   Monitor* m1 = (Monitor*)minfo1;
   Monitor* m2 = (Monitor*)minfo2;
   
   if (m1->area > m2->area) {
      return -1;
   }
   if (m1->w > m2->w) {
      return -1;
   }
   if (m1->h > m2->h) {
      return -1;
   }
   if (m1->info.x1 < m2->info.x1) {
      return -1;
   }
   if (m1->info.y1 < m2->info.y1) {
      return -1;
   }
   return 1;

}





/// ------------------------     DisplayModes     ------------------------------------------



void DisplayModes::SortModes() {
///void qsort (void* base, size_t num, size_t size,
///            int (*compar)(const void*,const void*));
   qsort(&mode_list[0] , mode_list.size() , sizeof(ALLEGRO_DISPLAY_MODE) , CompareDisplayModes);
}



void DisplayModes::RefreshModes() {
   mode_list.clear();
   for (int i = 0 ; i < al_get_num_display_modes() ; ++i) {
      ALLEGRO_DISPLAY_MODE mode;
      al_get_display_mode(i , &mode);
      mode_list.push_back(mode);
   }
   SortModes();
}



/// ------------------------     Monitor     ------------------------------------------



void Monitor::SetInfo(int monitor_number , ALLEGRO_MONITOR_INFO monitor_info) {
   monitor_num = monitor_number;
   info = monitor_info;
   w = info.x2 - info.x1;
   h = info.y2 - info.y1;
   area = w*h;
   
   al_set_new_display_adapter(monitor_num);
   
   modes.RefreshModes();
   
}



/// ------------------------     MonitorInfo     ------------------------------------------



MonitorInfo::MonitorInfo() :
      monitors()
{}



void MonitorInfo::RefreshMonitorInfo() {
   monitors.clear();
   for (int i = 0 ; i < al_get_num_video_adapters() ; ++i) {
      ALLEGRO_MONITOR_INFO info;
      al_get_monitor_info(i , &info);
      Monitor m;
      m.SetInfo(i , info);
      monitors.push_back(m);
   }
   qsort(&monitors[0] , monitors.size() , sizeof(Monitor) , CompareMonitors);
}



bool MonitorInfo::GetMonitorData(int monitor_num , Monitor* pmonitor) {
   if (monitor_num < 0 || monitor_num >= NumMonitors()) {return false;}
   if (!pmonitor) {return false;}
   *pmonitor = monitors[monitor_num];
   return true;
}



int MonitorInfo::GetMonitorWidth(int monitor_num) {
   if (monitor_num < 0 || monitor_num >= (int)monitors.size()) {return 0;}
   Monitor& m = monitors[monitor_num];
   return m.w;
}



int MonitorInfo::GetMonitorHeight(int monitor_num) {
   if (monitor_num < 0 || monitor_num >= (int)monitors.size()) {return 0;}
   Monitor& m = monitors[monitor_num];
   return m.h;
}



int MonitorInfo::GetMonitorArea(int monitor_num) {
   if (monitor_num < 0 || monitor_num >= (int)monitors.size()) {return 0;}
   Monitor& m = monitors[monitor_num];
   return m.area;
}



int MonitorInfo::GetAdapterNum(int monitor_num) {
   if (monitor_num < 0 || monitor_num >= (int)monitors.size()) {return 0;}
   Monitor& m = monitors[monitor_num];
   return m.monitor_num;
}



bool MonitorInfo::GetMonitorModes(int monitor_num , DisplayModes* pmodes) {
   if (monitor_num < 0 || monitor_num >= (int)monitors.size()) {return false;}
   if (!pmodes) {return false;}
   *pmodes = monitors[monitor_num].modes;
   return true;
}





