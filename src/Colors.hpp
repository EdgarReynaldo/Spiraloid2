


#ifndef Colors_HPP
#define Colors_HPP

#include "Array.hpp"
#include "Values.hpp"
#include "RefreshRate.hpp"

#include "allegro5/allegro.h"


#include "Inline.hpp"



class Colorset {

private :
   
   Value num_colors_value;
   Value num_shades_value;

   Array<ALLEGRO_COLOR> colorset;
   Value color_index_value;
   Value color_cycle_rate;
   Value color_index_start_value;
   bool color_cycle_forward;
   
   int civ_factor;
   int civ_exponent;
   
   ALLEGRO_COLOR colors[12];
   
   bool flip_colors;
   
   bool needs_refresh;
   
   
   

   Colorset(const Colorset& cs) {(void)cs;}
   Colorset& operator=(const Colorset& cs) {(void)cs;return *this;}
   
      
public :
   void RecalculateColors();

      
   Colorset() :
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
      
///      RecalculateColors();
      
   }
   
   void SetRainbowColors();
   
   void SetColors(float* twelve_hsl_quartets);
   
   void ResetColorIndex() {color_index_value.SetValue((double)color_index_start_value);}
   
   INLINE const ALLEGRO_COLOR& GetNextColor() {
      return colorset[(unsigned int)(double)(color_index_value++)];
   }
   INLINE unsigned int Size() {return colorset.Size();}
   
   INLINE void Refresh() {RecalculateColors();}
   
   void Update(double dt);
};




#endif // Colors_HPP
