


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

   Colorset();
   
   void SetRainbowColors();
   
   void SetColors(float* twelve_hsl_quartets);
   
   void FlipColors(bool flip);
   bool Flip() {return flip_colors;}
   
   Value& ColorIndexStartValue() {return color_index_start_value;}
   Value& ColorCycleRate() {return color_cycle_rate;}
   
   Value& NumShades() {return num_shades_value;}
   Value& NumColors() {return num_colors_value;}
   
   
   void ResetColorIndex() {color_index_value.SetValue((double)color_index_start_value);}
   
   INLINE const ALLEGRO_COLOR& GetNextColor() {
      return colorset[(unsigned int)(double)(color_index_value++)];
   }
   INLINE unsigned int Size() {return colorset.Size();}
   
   INLINE void Refresh() {RecalculateColors();}
   
   void Update(double dt);
};




#endif // Colors_HPP
