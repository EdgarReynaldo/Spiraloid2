


#include "Spirals.hpp"
#include "Equations.hpp"

#include <cmath>
#include <cstdio>


#include "allegro5/allegro_primitives.h"



void Spiral2D::GeneratePlotData() {

   if (spiral_needs_refresh) {
      double num_data = (theta_stop - theta_start)/theta_delta;
      num_data = ceil(num_data);
      
      Assert(num_data >= 1.0);
      
      unsigned int data_size = (unsigned int)num_data;
      
      spiral_data_original.Allocate(data_size);
      spiral_data_modified.Allocate(data_size);

      SpiralEquation2D spiral_eq;
      
      spiral_eq.radial_delta = radial_delta;
      
      double theta = theta_start;

      unsigned int data_num = 0;
      while (data_num < data_size) {
         Pos2D p = spiral_eq.Evaluate(theta);
         DataOriginal(data_num) = p;
         theta += theta_delta;
         ++data_num;
      }
      spiral_needs_refresh = false;
      transform_needs_refresh = true;
   }

}



void Spiral2D::SetSpiralParameters(double rdelta , double tstart , double tstop , double tdelta) {
   /// Check parameters here...
   if (rdelta <= 0.0) {
      throw Exception("void Spiral2D::SetParameters(...) : rdelta non-positive!\n");
   }
   if ((tstop - tstart) <= 0.0) {
      throw Exception("void Spiral2D::SetParameters(...) : theta range non-positive!\n");
   }
   if (tdelta <= 0.0) {
      throw Exception("void Spiral2D::SetParameters(...) : tdelta non-positive!\n");
   }

   if (rdelta != radial_delta ||
      tstart != theta_start ||
      tstop != theta_stop ||
      tdelta != theta_delta)
   {
      spiral_needs_refresh = true;
   }

   radial_delta = rdelta;
   theta_start = tstart;
   theta_stop = tstop;
   theta_delta = tdelta;
}



void Spiral2D::SetTransformParameters(double cx , double cy , double sx , double sy , double rotate_degrees) {
   if (cx != centerx ||
       cy != centery ||
       sx != scalex || 
       sy != scaley || 
       rotate_degrees != rotation_degrees)
   {
      transform_needs_refresh = true;
   }
   centerx = cx;
   centery = cy;
   scalex = sx;
   scaley = sy;
   rotation_degrees = rotate_degrees;
}






void Spiral2D::Refresh() {
   if (spiral_needs_refresh) {
      GeneratePlotData();
   }
   if (transform_needs_refresh) {
      /// Refresh modified data from original using transform
      al_identity_transform(&transform);
      al_rotate_transform(&transform , rotation_degrees*(M_PI/180.0));
      al_scale_transform(&transform , scalex , scaley);
      al_translate_transform(&transform , centerx , centery);
      for (unsigned int i = 0 ; i < Size() ; ++i) {
         Pos2D mod = DataOriginal(i);
         /// TODO : This is a hack
         float x = mod.x;
         float y = mod.y;
         al_transform_coordinates(&transform , &x , &y);
         mod.x = x;
         mod.y = y;
         DataModified(i) = mod;
      }
      transform_needs_refresh = false;
   }
}



/// -------------------------------      Spiraloid class       -------------------------------------------



void Spiraloid::GenerateSpiralData() {
   
   spiral1.SetSpiralParameters(radial_delta_value , theta_start , theta_stop , theta_delta_value);
   spiral2.SetSpiralParameters(radial_delta_value , theta_start + (double)theta_offset_value , theta_stop + (double)theta_offset_value , theta_delta_value);
   
   spiral1.SetTransformParameters(centerx , centery , scalex , scaley , rotation_degrees_value);
   spiral2.SetTransformParameters(centerx , centery , scalex , scaley , rotation_degrees_value);
   
   spiral1.Refresh();
   spiral2.Refresh();
}



void Spiraloid::SetSpiraloidParameters(const double rdelta , const double tstart , const double tstop , const double tdelta , const double toffset) {
   if (rdelta != (double)radial_delta_value ||
       tstart != theta_start ||
       tstop != theta_stop ||
       tdelta != (double)theta_delta_value ||
       toffset != (double)theta_offset_value) {
      needs_refresh = true;
   }
   radial_delta_value = rdelta;
   theta_start = tstart;
   theta_stop = tstop;
   theta_delta_value = tdelta;
   theta_offset_value = toffset;
}



void Spiraloid::SetSpiraloidTransform(const double cx , const double cy , const double sx , const double sy) {
   if (cx != centerx ||
       cy != centery ||
       sx != scalex ||
       sy != scaley) {
      needs_refresh = true;
   }
   centerx = cx;
   centery = cy;
   scalex = sx;
   scaley = sy;
   printf("Spiraloid::SetSpiraloidTransform() : cx,cy,sx,sy = %14.8lf , %14.8lf , %14.8lf , %14.8lf\n" , cx , cy , sx , sy);
}
   


void Spiraloid::SetRotation(const double rotate_degrees) {
   if (rotate_degrees != (double)rotation_degrees_value) {
      needs_refresh = true;
   }
   rotation_degrees_value = rotate_degrees;
}



void Spiraloid::SetRotationRate(double degrees_per_second) {
   if (degrees_per_second != (double)rotation_dps_value) {
      needs_refresh = true;
   }
   rotation_dps_value = degrees_per_second;
}




Value& Spiraloid::RadialDeltaValue() {
   needs_refresh = true;
   return radial_delta_value;
}



Value& Spiraloid::ThetaDeltaValue() {
   needs_refresh = true;
   return theta_delta_value;
}



Value& Spiraloid::RotationDegreesValue() {
   needs_refresh = true;
   return rotation_degrees_value;
}



Value& Spiraloid::RotationDPSValue() {
   needs_refresh = true;
   return rotation_dps_value;
}



Value& Spiraloid::ThetaOffsetValue() {
   needs_refresh = true;
   return theta_offset_value;
}



Value& Spiraloid::LineThicknessValue() {
   needs_refresh = true;
   return line_thickness_value;
}


Value& Spiraloid::SpiralDrawingOptionValue() {
   needs_refresh = true;
   return spiral_drawing_option_value;
}



Value& Spiraloid::CircleRadiusValue() {
   needs_refresh = true;
   return circle_radius_value;
}



#define DRAW_SPIRALOID(draw_func) \
   for (unsigned int i = 1 ; i < spiral1.Size() ; ++i) { \
      Pos2D sp1 = spiral1.DataModified(i); \
      Pos2D sp2 = spiral2.DataModified(i); \
      double x1 = sp1.x; \
      double y1 = sp1.y; \
      double x2 = sp2.x; \
      double y2 = sp2.y; \
      draw_func(x1,y1,x2,y2,colorset.GetNextColor()); \
   }

///      void DrawOption1(double x1 , double y1 , double x2 , double y2 , ALLEGRO_COLOR col);

void Spiraloid::Draw() {

   colorset.ResetIndex();
   switch (spiral_drawing_option_value.IVal()) {
   case 1 :
      DRAW_SPIRALOID(DrawOption1);
      break;
   case 2 :
      DRAW_SPIRALOID(DrawOption2);
      break;
   case 3 :
      DRAW_SPIRALOID(DrawOption3);
      break;
   case 4 :
      DRAW_SPIRALOID(DrawOption4);
      break;
   }

}



void Spiraloid::Update(double dt) {
   
//   printf("Before update, rotation_degrees_value::ival == %d\n" , (int)rotation_degrees_value.IVal());
   double old_rotation = (double)rotation_degrees_value;
   double new_rotation = old_rotation + (double)rotation_dps_value*dt;
   if (new_rotation != old_rotation) {
      needs_refresh = true;
   }
   rotation_degrees_value = new_rotation;
///   double new_rotation_value = (double)rotation_degrees_value;
///   printf("Old rotation = %12.8lf , new rotation = %12.8lf , new value = %12.8lf\n" , old_rotation , new_rotation , new_rotation_value);
//   printf("After update, rotation_degrees_value::ival == %d\n" , (int)rotation_degrees_value.IVal());

}



void Spiraloid::Refresh() {
   if (needs_refresh) {
      GenerateSpiralData();
      
      needs_refresh = false;
   }
}
