


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
   
   
public :
   
  void RecalculateColors();

   Colorset();
   Colorset(const Colorset& cs);
   Colorset& operator=(const Colorset& cs);

   void SetRainbowColors();
   
   void SetColors(float* twelve_hsl_quartets);
   
   void FlipColors(bool flip);
   bool Flip() {return flip_colors;}
   
   Value& ColorIndexStartValue() {return color_index_start_value;}
   Value& ColorCycleRate() {return color_cycle_rate;}
   
   Value& NumShades() {return num_shades_value;}
   Value& NumColors() {return num_colors_value;}
   
   
   void ResetColorIndex() {color_index_value.SetValue((double)color_index_start_value);}
   
//   INLINE ALLEGRO_COLOR& Color(unsigned int index);
   INLINE ALLEGRO_COLOR& Color(unsigned int index) {
      EAGLE_ASSERT(index < 12);
      return colors[index];
      needs_refresh = true;
   }
   
//   INLINE const ALLEGRO_COLOR& GetMainColor(unsigned int index);
   INLINE const ALLEGRO_COLOR& GetMainColor(unsigned int index) {
      EAGLE_ASSERT(index < 12);
      return colors[index];
   }
   
   INLINE const ALLEGRO_COLOR& GetNextColor() {
      return colorset[(unsigned int)(double)(color_index_value++)];
   }
   INLINE unsigned int Size() {return colorset.Size();}
   
   void Refresh();
   
   void Update(double dt);
   
//   void PrintColors();
   void PrintColors() {
      for (unsigned int i = 0 ; i < colorset.Size() ; ++i) {
         unsigned char r,g,b,a;
         al_unmap_rgba(colorset[i] , &r , &g , &b , &a);
         EagleInfo() << i << " " << (int)r << "," << (int)g << "," << (int)b << "," << (int)a << std::endl;
      }
   }
   
   void PrintColors2();
};




#endif // Colors_HPP
