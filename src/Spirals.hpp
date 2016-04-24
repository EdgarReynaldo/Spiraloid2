


#ifndef Spirals_HPP
#define Spirals_HPP



#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"


#include "Array.hpp"
#include "Values.hpp"
#include "Position.hpp"
#include "Colors.hpp"
#include "Inline.hpp"



class Spiral2D {
   
private :
   /// Spiral data
   double radial_delta;
   
   double theta_start;
   double theta_stop;
   double theta_delta;
   
   bool spiral_needs_refresh;
   
   /// Transform data
   double centerx;
   double centery;
   double scalex;
   double scaley;
   double rotation_degrees;
   
   ALLEGRO_TRANSFORM transform;
   
   bool transform_needs_refresh;
   
   /// Spiral data arrays
   Array<Pos2D> spiral_data_original;
   Array<Pos2D> spiral_data_modified;

   
   
   void GeneratePlotData();

public :
   
///   Spiral2D();
   Spiral2D() :
         radial_delta(0.0),
         theta_start(0.0),
         theta_stop(0.0),
         theta_delta(1.0),
         spiral_needs_refresh(true),
         centerx(0.0),
         centery(0.0),
         scalex(0.0),
         scaley(0.0),
         rotation_degrees(0.0),
         transform(),
         transform_needs_refresh(true),
         spiral_data_original(),
         spiral_data_modified()
   {}
   
   
   unsigned int Size() {return spiral_data_modified.Size();}
   Pos2D& DataOriginal(unsigned int index) {return spiral_data_original.Data(index);}
   Pos2D& DataModified(unsigned int index) {return spiral_data_modified.Data(index);}

   void SetSpiralParameters(double rdelta , double tstart , double tstop , double tdelta);
   void SetTransformParameters(double cx , double cy , double sx , double sy , double rotate_degrees);

   void Refresh();

};



class Spiraloid {
   
   
private :
   
   /// Spiral data
   Value radial_delta_value;
   Value theta_delta_value;
   
   double theta_start;
   double theta_stop;
   
   /// Transform data
   double centerx;
   double centery;
   double scalex;
   double scaley;
   
   /// Drawing parameters
   Value rotation_degrees_value;
   Value rotation_dps_value;/// Rotation in degrees per second
   Value theta_offset_value;/// Offset for second spiral, formerly known as 'user_angle'
   Value line_thickness_value;/// Pixel width of lines

   /// Options
   Value spiral_drawing_option_value;
   Value circle_radius_value;

   ///
   Colorset colorset;
   
///   Value colorset_index_value;
   
   /// Spirals
   Spiral2D spiral1;
   Spiral2D spiral2;
   
   bool needs_refresh;
   


   void GenerateSpiralData();

public :
   
//   Spiraloid();
   Spiraloid() :
         radial_delta_value(),
         theta_delta_value(),
         theta_start(0.0),
         theta_stop(0.0),
         centerx(0.0),
         centery(0.0),
         scalex(0.0),
         scaley(0.0),
         rotation_degrees_value(),
         rotation_dps_value(),
         theta_offset_value(),
         line_thickness_value(),
         spiral_drawing_option_value(),
         circle_radius_value(),
         spiral1(),
         spiral2(),
         needs_refresh(true)
         
   {
      radial_delta_value.SetValues(0 , 10000 , 1000000 , -2);
      theta_delta_value.SetValues(100 , 100 , 36000*3 , -2);
      rotation_degrees_value.SetValues(0 , 0 , 35999 , -2 , true);
      rotation_dps_value.SetValues(-36000*60 , 0 , 36000*60 , -2);
      theta_offset_value.SetValues(0 , 36000 , 36000*3 , -2);
      line_thickness_value.SetValues(1 , 100 , 10000 , -2);
      
      spiral_drawing_option_value.SetValues(1 , 1 , 4 , 0 , true);
      circle_radius_value.SetValues(1,100,10000,-1);
   }
   
   void SetSpiraloidParameters(const double rdelta , const double tstart , const double tstop , const double tdelta , const double toffset);
   void SetSpiraloidTransform(const double cx , const double cy , const double sx , const double sy);
   void SetRotation(const double rotate_degrees);
   void SetRotationRate(double degrees_per_second);/// Positive is clockwise
   

   /// Direct access to parameters, gives control to user
   Value& RadialDeltaValue();
   Value& ThetaDeltaValue();
   Value& RotationDegreesValue();
   Value& RotationDPSValue();
   Value& ThetaOffsetValue();
   Value& LineThicknessValue();

   Value& SpiralDrawingOptionValue();
   Value& CircleRadiusValue();
   
   void Draw();

private :
   
/**
   INLINE void DrawOption1(double x1 , double y1 , double x2 , double y2 , ALLEGRO_COLOR col);
   INLINE void DrawOption2(double x1 , double y1 , double x2 , double y2 , ALLEGRO_COLOR col);
   INLINE void DrawOption3(double x1 , double y1 , double x2 , double y2 , ALLEGRO_COLOR col);
   INLINE void DrawOption4(double x1 , double y1 , double x2 , double y2 , ALLEGRO_COLOR col);
   INLINE void DrawOption5(double x1 , double y1 , double x2 , double y2 , ALLEGRO_COLOR col);
   INLINE void DrawOption6(double x1 , double y1 , double x2 , double y2 , ALLEGRO_COLOR col);
   INLINE void DrawOption7(double x1 , double y1 , double x2 , double y2 , ALLEGRO_COLOR col);
//*/

/// INLINE SPIRALOID FUNCTIONS


void INLINE DrawOption1(double x1 , double y1 , double x2 , double y2 , ALLEGRO_COLOR col) {
   al_draw_line(x1 , y1 , x2 , y2 , col , (double)LineThicknessValue());
}



void INLINE DrawOption2(double x1 , double y1 , double x2 , double y2 , ALLEGRO_COLOR col) {
   al_draw_line(x1 , y2 , x2 , y1 , col , (double)LineThicknessValue());
}



void INLINE DrawOption3(double x1 , double y1 , double x2 , double y2 , ALLEGRO_COLOR col) {
   double cx = (x1 + x2)/2.0;
   double cy = (y1 + y2)/2.0;
   double hx = x2 - cx;
   double hy = y2 - cy;
   double x3 = cx + hy;
   double y3 = cy + hx;
   double x4 = cx - hy;
   double y4 = cy - hx;
   al_draw_line(x3,y3,x4,y4,col , (double)LineThicknessValue());
}



void INLINE DrawOption4(double x1 , double y1 , double x2 , double y2 , ALLEGRO_COLOR col) {
   double cx = (x1 + x2)/2.0;
   double cy = (y1 + y2)/2.0;
   al_draw_circle(cx , cy , (double)CircleRadiusValue() , col , (double)LineThicknessValue());
}

   
   
public :
   void Update(double dt);

   void Refresh();

};



/*
void Spiraloid::DrawOption5(double x1 , double y1 , double x2 , double y2 , ALLEGRO_COLOR col) {
   
}



void Spiraloid::DrawOption6(double x1 , double y1 , double x2 , double y2 , ALLEGRO_COLOR col) {
   
}



void Spiraloid::DrawOption7(double x1 , double y1 , double x2 , double y2 , ALLEGRO_COLOR col) {
   
}
*/




#endif // Spirals_HPP







