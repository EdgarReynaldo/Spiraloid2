


#include "Spirals.hpp"
#include "Display.hpp"


#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_image.h"



#include <cstdio>



int main(int argc , char** argv) {
   
   (void)argc;
   (void)argv;
   
   if (!al_init()) {
      return 1;
   }

   if (!al_init_primitives_addon()) {
      return 2;
   }
   if (!al_init_image_addon()) {
      return 3;
   }
   if (!al_install_keyboard()) {
      return 4;
   }
   
   
   al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_FULLSCREEN_WINDOW);
   
   int fsw = 1920;
   int fsh = 1080;
   int ww = 800;
   int wh = 600;
   
   bool fullscreen = false;

   Display display;
   if (!display.Create(fullscreen , fsw , fsh , ww , wh)) {
      return 5;
   }
   al_clear_to_color(al_map_rgb(0,0,255));
   display.Flip();

   ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
   
   ALLEGRO_TIMER* timer = al_create_timer(1.0/60.0);
   
   al_register_event_source(queue , al_get_keyboard_event_source());
   al_register_event_source(queue , al_get_timer_event_source(timer));
   al_register_event_source(queue , al_get_display_event_source(display));
   
   bool clear_buffer = true;
   bool temp_clear = false;
   bool redraw = true;
   bool quit = false;
   bool keys_down[ALLEGRO_KEY_MAX];
   memset(&keys_down , 0 , sizeof(keys_down));
   

   al_start_timer(timer);

   char charbuf[1024];
   memset(charbuf , 0 , 1024);
   
   while (!quit) {
   
      if (redraw) {
         
         display.DrawToBuffer();
         if (clear_buffer || temp_clear) {
            al_clear_to_color(al_map_rgb(0,0,0));
            temp_clear = false;
         }
         spiraloid.Draw();
         display.Flip();
         
         redraw = false;
      }

      do {
         ALLEGRO_EVENT ev;
         al_wait_for_event(queue , &ev);

         if (ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {
            printf("ALLEGRO_EVENT_DISPLAY_RESIZE received.\n");
            display.AcknowledgeResize();
            spiraloid.SetSpiraloidTransform(display.CX() , display.CY() , display.SX() , display.SY());
            redraw = true;

/*         

            al_destroy_bitmap(buffer);
            al_acknowledge_resize(display);
            width = al_get_display_width(display);
            height = al_get_display_height(display);
            buffer = al_create_bitmap(width , height);
            al_set_target_bitmap(buffer);
            al_clear_to_color(al_map_rgb(0,0,0));
            cx = width/2.0;
            cy = height/2.0;
*/
         }
         
         if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            keys_down[ev.keyboard.keycode] = true;
            if (ev.keyboard.keycode == ALLEGRO_KEY_I) {
               clear_buffer = !clear_buffer;
               redraw = true;
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_F) {
               fullscreen = !fullscreen;
               display.ToggleFullscreen();
               spiraloid.SetSpiraloidTransform(display.CX() , display.CY() , display.SX() , display.SY());
               al_register_event_source(queue , al_get_display_event_source(display));
               redraw = true;
//               al_toggle_display_flag(display , ALLEGRO_FULLSCREEN_WINDOW , fullscreen);
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_S) {
               if (keys_down[ALLEGRO_KEY_LCTRL] || keys_down[ALLEGRO_KEY_RCTRL]) {
                  /// Screen shot
                  display.SaveScreenie();
/*                  
                  do {
                     sprintf(charbuf , "Screenie%d.png" , screenie_num);
                     ++screenie_num;
                  } while (al_filename_exists(charbuf));
                  if (!al_save_bitmap(charbuf , buffer)) {
                     printf("Failed to save bitmap %s\n" , charbuf);
                  }
*/
               }
            }
         }
         if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            keys_down[ev.keyboard.keycode] = false;
         }

         if (ev.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
            
            if (keys_down[ALLEGRO_KEY_A]) {
               temp_clear = true;
               redraw = true;
            }

            int modifier = 100;
            if (keys_down[ALLEGRO_KEY_LCTRL] || keys_down[ALLEGRO_KEY_RCTRL]) {
               modifier = 10;
            }
            if (keys_down[ALLEGRO_KEY_ALT] || keys_down[ALLEGRO_KEY_ALTGR]) {
               modifier = 1;
            }
            
            if (keys_down[ALLEGRO_KEY_LSHIFT] || keys_down[ALLEGRO_KEY_RSHIFT]) {
//               printf("Key SHIFT down\n");
///               double dold_dps = spiraloid.RotationDPSValue();
///               int old_dps = spiraloid.RotationDPSValue().IVal();
               if (keys_down[ALLEGRO_KEY_PAD_3] || keys_down[ALLEGRO_KEY_PAD_1]) {
//                  printf("Rotation key down\n");
                  if (keys_down[ALLEGRO_KEY_PAD_3]) {
                     spiraloid.RotationDPSValue() += modifier;
                  }
                  if (keys_down[ALLEGRO_KEY_PAD_1]) {
                     spiraloid.RotationDPSValue() -= modifier;
                  }
///                  double d_dps = spiraloid.RotationDPSValue();
///                  int dps = spiraloid.RotationDPSValue().IVal();
//                  printf("RotationDPSValue : IVal (%d , %d) , DVal (%14.8lf , %14.8lf) , modifier (%d)\n" , old_dps , dps , dold_dps , d_dps , modifier);
               }
            }
            else {
               if (keys_down[ALLEGRO_KEY_PAD_3]) {
                  spiraloid.RotationDegreesValue() += modifier;
               }
               if (keys_down[ALLEGRO_KEY_PAD_1]) {
                  spiraloid.RotationDegreesValue() -= modifier;
               }
            }

            if (keys_down[ALLEGRO_KEY_LSHIFT] || keys_down[ALLEGRO_KEY_RSHIFT]) {
               modifier = 1000;
            }

            if (keys_down[ALLEGRO_KEY_PAD_6]) {
               spiraloid.ThetaDeltaValue() += modifier;
            }
            if (keys_down[ALLEGRO_KEY_PAD_4]) {
               spiraloid.ThetaDeltaValue() -= modifier;
            }
            if (keys_down[ALLEGRO_KEY_PAD_PLUS]) {
               spiraloid.ThetaOffsetValue() += modifier;
            }
            if (keys_down[ALLEGRO_KEY_PAD_MINUS]) {
               spiraloid.ThetaOffsetValue() -= modifier;
            }
            if (keys_down[ALLEGRO_KEY_COMMA]) {
               spiraloid.LineThicknessValue() -= modifier;
               printf("LTV == %8.4lf\n" , (double)spiraloid.LineThicknessValue());
            }
            if (keys_down[ALLEGRO_KEY_FULLSTOP]) {
               spiraloid.LineThicknessValue() += modifier;
               printf("LTV == %8.4lf\n" , (double)spiraloid.LineThicknessValue());
            }
            
            
            if (keys_down[ALLEGRO_KEY_ESCAPE]) {
               quit = true;
            }
            
            spiraloid.Update(al_get_timer_speed(ev.timer.source));
            
//            printf("Rotation = %14.8lf , Rotation DPS = %14.8lf\n" , (double)spiraloid.RotationDegreesValue() , (double)spiraloid.RotationDPSValue());
            
         }
         if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            quit = true;
         }
         
         spiraloid.Refresh();
         
         if (quit) {break;}
      } while (!al_is_event_queue_empty(queue));
      
      
         
         
   }
   
   
   return 0;
}

