

#include "Colors.hpp"


#include "allegro5/allegro_color.h"


/// h,s,l triplets
float rainbow_colorset[12][4] = {
   {0.0,1.0,0.5,1.0},
   {30.0,1.0,0.5,1.0},
   {60.0,1.0,0.5,1.0},
   {90.0,1.0,0.5,1.0},
   {120.0,1.0,0.5,1.0},
   {150.0,1.0,0.5,1.0},
   {180.0,1.0,0.5,1.0},
   {210.0,1.0,0.5,1.0},
   {240.0,1.0,0.5,1.0},
   {270.0,1.0,0.5,1.0},
   {300.0,1.0,0.5,1.0},
   {330.0,1.0,0.5,1.0}
};


float colorset1[12][4] = {
   {60,1.0,0.0,1.0},
   {60,1.0,0.5,1.0},
   {60,1.0,1.0,1.0},
   {90,1.0,1.0,1.0},
   {90,1.0,0.5,1.0},
   {90,1.0,0.0,1.0},
   {120,1.0,0.0,1.0},
   {120,1.0,0.5,1.0},
   {120,1.0,1.0,1.0},
   {150,1.0,1.0,1.0},
   {150,1.0,0.5,1.0},
   {150,1.0,0.0,1.0}
};

#define NUM_COLORSETS 2

float* colorsets[NUM_COLORSETS] = {
   rainbow_colorset,
   colorset1
};

void Colorset::RecalculateColors() {
   if (!needs_refresh) {
      return;
   }
   const int total_num_colors = 2*(int)num_colors_value*(int)num_shades_value;
   
   colorset.Allocate((unsigned int)total_num_colors);
   
   for (int c = 0 ; c < num_colors_value.IVal() ; ++c) {
      unsigned char r,g,b,a;
      double dr,dg,db,da,dr2,dg2,db2,da2;
      al_unmap_rgba(colors[c] , &r , &g , &b , &a);
      dr = r;
      dg = g;
      db = b;
      da = a;
      al_unmap_rgba(colors[(c + 1)%12] , &r , &g , &b , &a);
      dr2 = r;
      dg2 = g;
      db2 = b;
      da2 = a;
      double num_shades = (double)num_shades_value.IVal();
      const double dr_delta = (dr2 - dr)/num_shades;
      const double dg_delta = (dg2 - dg)/num_shades;
      const double db_delta = (db2 - db)/num_shades;
      const double da_delta = (da2 - da)/num_shades;
      unsigned int index = (unsigned int)c*num_shades_value.IVal();
      for (int s = 0 ; s < num_shades_value.IVal() ; ++s) {
         colorset[(total_num_colors - 1) - index] = colorset[index] = al_map_rgba((int)dr , (int)dg , (int)db , (int)da);
         ++index;
         dr += dr_delta;
         dg += dg_delta;
         db += db_delta;
         da += da_delta;
      }
   }
   
   color_index_value.SetValues(0 , color_index_value.IVal() , total_num_colors*civ_factor - 1 , civ_exponent , true);
   
   needs_refresh = false;
}



void Colorset::SetRainbowColors() {
   
///void al_color_hsl_to_rgb(float hue, float saturation, float lightness,
///   float *red, float *green, float *blue)
   
   for (int i = 0 ; i < 12 ; ++i) {
      float r,g,b;
      double h = (double)i*30.0;
      double s = 1.0;
      double l = 0.5;
      al_color_hsl_to_rgb(h,s,l,&r,&g,&b);
      colors[i] = al_map_rgba_f(r,g,b,1.0f);
   }

   needs_refresh = true;
}



void Colorset::SetColors(float* twelve_hsla_quartets) {
   float r,g,b;
   float* val = twelve_hsla_quartets;
   for (int i = 0 ; i < 12 ; ++i) {
         float h = val[4*i + 0];
         float s = val[4*i + 1];
         float l = val[4*i + 2];
         float a = val[4*i + 3];
         al_color_hsl_to_rgb(h,s,l,&r,&g,&b);
         colors[i] = al_map_rgba_f(r,g,b,a);
   }
   needs_refresh = true;
}





