

#include "Colors.hpp"

#include "Eagle/backends/Allegro5/Allegro5Color.hpp"
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
   &rainbow_colorset[0][0],
   &colorset1[0][0]
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
         ALLEGRO_COLOR c = al_map_rgba((unsigned char)dr , (unsigned char)dg , (unsigned char)db , (unsigned char)da);
         colorset[index] = c;
         if (flip_colors) {
            colorset[(total_num_colors - 1) - index] = c;
         }
         else {
            colorset[index + total_num_colors/2] = c;
         }
         ++index;
         dr += dr_delta;
         dg += dg_delta;
         db += db_delta;
         da += da_delta;
      }
   }
   
   color_index_start_value.SetValues(0 , 0 , total_num_colors - 1 , 0 , true);
   color_index_value.SetValues(0 , 0 , total_num_colors -1 , 0 , true);
   
   needs_refresh = false;
}



Colorset::Colorset() :
      num_colors_value(),
      num_shades_value(),
      colorset(),
      color_index_value(),
      color_cycle_rate(),
      color_index_start_value(),
      color_cycle_forward(true),
      civ_factor(0),
      civ_exponent(0),
      colors(),
      flip_colors(false),
      needs_refresh(true)
{
   num_colors_value.SetValues(1,12,12,0);
   num_shades_value.SetValues(1,30,360,0);
   
   civ_factor = 100;
   civ_exponent = -2;
   
   color_index_value.SetValues(0,0,0,0,true);
   color_cycle_rate.SetValues(0,100*REFRESHRATE,36000*REFRESHRATE,-2);
   color_index_start_value.SetValues(0,0,0,0,true);
   
   memset(&colors , 0 , 12*sizeof(ALLEGRO_COLOR));
   
   SetRainbowColors();
}



Colorset::Colorset(const Colorset& cs) :
      num_colors_value(cs.num_colors_value),
      num_shades_value(cs.num_shades_value),
      colorset(cs.colorset),
      color_index_value(cs.color_index_value),
      color_cycle_rate(cs.color_cycle_rate),
      color_index_start_value(cs.color_index_start_value),
      color_cycle_forward(cs.color_cycle_forward),
      civ_factor(cs.civ_factor),
      civ_exponent(cs.civ_exponent),
      colors(),
      flip_colors(cs.flip_colors),
      needs_refresh(true)
{
   for (unsigned int i = 0 ; i < 12 ; ++i) {
      this->colors[i] = cs.colors[i];
   }
}



Colorset& Colorset::operator=(const Colorset& cs) {
   this->num_colors_value = cs.num_colors_value;
   this->num_shades_value = cs.num_shades_value;
   this->colorset = cs.colorset;
   this->color_index_value = cs.color_index_value;
   this->color_cycle_rate = cs.color_cycle_rate;
   this->color_index_start_value = cs.color_index_start_value;
   this->color_cycle_forward = cs.color_cycle_forward;
   this->civ_factor = cs.civ_factor;
   this->civ_exponent = cs.civ_exponent;
   for (unsigned int i = 0 ; i < 12 ; ++i) {
      this->colors[i] = cs.colors[i];
   }
   this->flip_colors = cs.flip_colors;
   this->needs_refresh = true;
   return *this;
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



void Colorset::FlipColors(bool flip) {
   flip_colors = flip;
   Refresh();
}



void Colorset::Update(double dt) {
   color_index_start_value += (double)color_cycle_rate*dt;
}



void Colorset::Refresh() {
   needs_refresh = true;
   RecalculateColors();
}



void Colorset::PrintColors2() {
   ResetColorIndex();
   for (unsigned int i = 0 ; i < colorset.Size() ; ++i) {
      EagleInfo() << i << " " << ::GetEagleColor(GetNextColor()) << std::endl;
   }
}
