

#define DEBUGMODE

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/debug.h>

ALLEGRO_DEBUG_CHANNEL("Resize test ");



int main(int argc, char **argv) {
   
   (void)argc;
   (void)argv;
   
    ALLEGRO_DISPLAY *display;
    ALLEGRO_BITMAP *temp = NULL;

    if (!al_init()) return -1;
    al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);
    display = al_create_display(500, 500);
    if (!display) return -1;
///    ALLEGRO_EVENT event;
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    al_register_event_source(queue, al_get_display_event_source(display));

    al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);
    
    temp = al_create_bitmap(100, 100);
    if (!temp) {
        printf("Failed to create temp video bitmap on attempt 1.\n");
    }
    for (int i = 0 ; i < 256 ; ++i) {
       ALLEGRO_DEBUG("Setting target bitmap to temp.\n");
       al_set_target_bitmap(temp);
       ALLEGRO_DEBUG("Clearing temp bitmap.\n");
       al_clear_to_color(al_map_rgb(0,0,255-i));
       ALLEGRO_DEBUG("Setting target bitmap to backbuffer.\n");
       al_set_target_backbuffer(display);
       ALLEGRO_DEBUG("Drawing bitmap.\n");
       al_draw_bitmap(temp , 0 , 0 , 0);
       ALLEGRO_DEBUG("Flipping display.\n");
       al_flip_display();
       ALLEGRO_DEBUG("Resting.\n");
       al_rest(0.004);
    }
    al_destroy_bitmap(temp);

//    al_set_target_backbuffer(display);
    if (!al_resize_display(display, 600, 400)) {
        printf("Failed to resize display.\n");
    }
    al_set_target_backbuffer(display);

///    al_rest(3.0);
    
    temp = al_create_bitmap(200, 200);
    if (!temp) {
        printf("Failed to create temp video bitmap on attempt 2.\n");
        al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);
        temp = al_create_bitmap(200,200);
    }

    for (int i = 0; i < 255; i++) {
        al_set_target_bitmap(temp);
        al_clear_to_color(al_map_rgb(0,i,0));
        al_set_target_backbuffer(display);
        al_draw_bitmap(temp, 0, 0, 0);
        al_flip_display();
//        al_rest(0.01);
    }

    return 0;
}
