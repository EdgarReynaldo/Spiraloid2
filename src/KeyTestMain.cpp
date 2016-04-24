
#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"

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
   
   if (!al_install_keyboard()) {
      return 3;
   }
   
   
   al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_WINDOWED);
   
   int width = 800;
   int height = 600;
   
   ALLEGRO_DISPLAY* display = al_create_display(width , height);
   
   al_clear_to_color(al_map_rgb(0,0,255));
   al_flip_display();
   
   ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
   
   ALLEGRO_TIMER* timer = al_create_timer(1.0/10.0);
   
   al_register_event_source(queue , al_get_keyboard_event_source());
   al_register_event_source(queue , al_get_timer_event_source(timer));
   al_register_event_source(queue , al_get_display_event_source(display));

   
   bool keys_down[ALLEGRO_KEY_MAX];
   memset(&keys_down , 0 , sizeof(keys_down));
   
   
   int npkeycode[10] = {
      ALLEGRO_KEY_PAD_0,
      ALLEGRO_KEY_PAD_1,
      ALLEGRO_KEY_PAD_2,
      ALLEGRO_KEY_PAD_3,
      ALLEGRO_KEY_PAD_4,
      ALLEGRO_KEY_PAD_5,
      ALLEGRO_KEY_PAD_6,
      ALLEGRO_KEY_PAD_7,
      ALLEGRO_KEY_PAD_8,
      ALLEGRO_KEY_PAD_9
   };
   
   const char* npkeycodestr[10] = {
      "ALLEGRO_KEY_PAD_0",
      "ALLEGRO_KEY_PAD_1",
      "ALLEGRO_KEY_PAD_2",
      "ALLEGRO_KEY_PAD_3",
      "ALLEGRO_KEY_PAD_4",
      "ALLEGRO_KEY_PAD_5",
      "ALLEGRO_KEY_PAD_6",
      "ALLEGRO_KEY_PAD_7",
      "ALLEGRO_KEY_PAD_8",
      "ALLEGRO_KEY_PAD_9"
   };
   
   al_start_timer(timer);

   bool quit = false;
   while (!quit) {
   
   
   
      do {
         ALLEGRO_EVENT ev;
         al_wait_for_event(queue , &ev);

         if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            quit = true;
         }
         if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            keys_down[ev.keyboard.keycode] = true;
            printf("%s key pressed\n" , al_keycode_to_name(ev.keyboard.keycode));
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
               quit = true;
            }
         }
         if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            printf("%s key released\n" , al_keycode_to_name(ev.keyboard.keycode));
            keys_down[ev.keyboard.keycode] = false;
         }

         if (ev.type == ALLEGRO_EVENT_TIMER) {
   
            if (keys_down[ALLEGRO_KEY_LSHIFT] || keys_down[ALLEGRO_KEY_RSHIFT]) {
               printf("Key SHIFT down ");
               
               bool npkeydown = false;
               for (int i = 0 ; i < 10 ; ++i) {
                  if (keys_down[npkeycode[i]]) {
                     npkeydown = true;
                  }
               }
               if (npkeydown) {
                  printf("Numpad key down : ");
                  for (int i = 0 ; i < 10 ; ++i) {
                     if (keys_down[npkeycode[i]]) {
                        printf("%s down " , npkeycodestr[i]);
                     }
                  }
               }
               else {
                  printf("Numpad keys all up ");
               }
            }
            else {
               printf("Key SHIFT up ");
               bool npkeydown = false;
               for (int i = 0 ; i < 10 ; ++i) {
                  if (keys_down[npkeycode[i]]) {
                     npkeydown = true;
                  }
               }
               if (npkeydown) {
                  printf("Numpad key down : ");
                  for (int i = 0 ; i < 10 ; ++i) {
                     if (keys_down[npkeycode[i]]) {
                        printf("%s down " , npkeycodestr[i]);
                     }
                  }
               }
               else {
                  printf("Numpad keys all up ");
               }
            }
            printf("\n");
         }
      } while (!al_is_event_queue_empty(queue));
   
   }
   return 0;
}

   
