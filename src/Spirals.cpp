


#include "Spirals.hpp"
#include "Equations.hpp"

#include <cmath>
#include <cstdio>


#include "allegro5/allegro_primitives.h"

#include "Eagle/Exception.hpp"



void Spiral2D::GeneratePlotData() {

   if (spiral_needs_refresh) {
      double num_data = (theta_stop - theta_start)/theta_delta;
      num_data = ceil(num_data);
      
      EAGLE_ASSERT(num_data >= 1.0);
      
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
      throw EagleException("void Spiral2D::SetParameters(...) : rdelta non-positive!\n");
   }
   if ((tstop - tstart) <= 0.0) {
      throw EagleException("void Spiral2D::SetParameters(...) : theta range non-positive!\n");
   }
   if (tdelta <= 0.0) {
      throw EagleException("void Spiral2D::SetParameters(...) : tdelta non-positive!\n");
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



Value& Spiraloid::RhombusXScaleValue() {
   needs_refresh = true;
   return rhombus_x_scale_value;
}



Value& Spiraloid::RhombusYScaleValue() {
   needs_refresh = true;
   return rhombus_y_scale_value;
}



Value& Spiraloid::RhombusDiagScaleValue() {
   needs_refresh = true;
   return rhombus_diag_scale_value;
}



void Spiraloid::Reset() {
   double radius = 100.0;
   double theta_start = 0.0;
   double theta_stop = 360.0*25.0;
   double theta_diff = 1.0;
   double theta_offset = 360.0;
   
   double rotation_degrees = 0.0;
   
   
   SetSpiraloidParameters(radius , theta_start , theta_stop , theta_diff , theta_offset);
   SetRotation(rotation_degrees);
   
   colorset.RecalculateColors();
   
   Refresh();
}
/**
#if 0
   #define FIX_THE_CENTER \
   if (fix_the_center) {\
      double theta = rotation_degrees_value();\
      int index = ?;\
      while (theta > -360.0) {\
            Pos2D p1 = spiral1.DataModified(index);\
      }\
   }\
#else
#endif // 0
   
//*/
#define FIX_THE_CENTER (void)0

#define DRAW_SPIRALOID(draw_func) \
   FIX_THE_CENTER;\
   for (unsigned int i = 0 ; i < spiral1.Size() ; ++i) { \
      Pos2D sp1 = spiral1.DataModified(i); \
      Pos2D sp2 = spiral2.DataModified(i); \
      double x1 = sp1.x; \
      double y1 = sp1.y; \
      double x2 = sp2.x; \
      double y2 = sp2.y; \
      ALLEGRO_COLOR c = colorset.GetNextColor();\
      draw_func(x1,y1,x2,y2,c); \
   }
///      void DrawOption1(double x1 , double y1 , double x2 , double y2 , ALLEGRO_COLOR col);

void Spiraloid::Draw(EagleGraphicsContext* win) {

   colorset.ResetColorIndex();
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
   case 5 :
      DRAW_SPIRALOID(DrawOption5);
      break;
   case 6 :
      DRAW_SPIRALOID(DrawOption6);
      break;
   }

}



void Spiraloid::Update(double dt) {
   
   double old_rotation = (double)rotation_degrees_value;
   double new_rotation = old_rotation + (double)rotation_dps_value*dt;
   if (new_rotation != old_rotation) {
      needs_refresh = true;
   }
   rotation_degrees_value = new_rotation;

   colorset.Update(dt);
}



void Spiraloid::Refresh() {
   if (needs_refresh) {
      GenerateSpiralData();
      
      needs_refresh = false;
   }
}




void Spiraloid::DrawOption5(double x1 , double y1 , double x2 , double y2 , ALLEGRO_COLOR col) {
   
   const double cx = (x1 + x2)/2.0;
   const double cy = (y1 + y2)/2.0;
   const double hx = x2 - cx;
   const double hy = y2 - cy;
   
   const double rxsv = (double)rhombus_x_scale_value;
   const double rysv = (double)rhombus_y_scale_value;
   double xpos1 = cx - (double)rysv*hx;
   double ypos1 = cy - (double)rysv*hy;
   double xpos2 = cx + (double)rysv*hx;
   double ypos2 = cy + (double)rysv*hy;
   double xpos3 = cx - (double)rxsv*hy;
   double ypos3 = cy + (double)rxsv*hx;
   double xpos4 = cx + (double)rxsv*hy;
   double ypos4 = cy - (double)rxsv*hx;


   al_draw_line(xpos1 , ypos1 , xpos4 , ypos4 , col , LineThicknessValue());
   al_draw_line(xpos4 , ypos4 , xpos2 , ypos2 , col , LineThicknessValue());
   al_draw_line(xpos2 , ypos2 , xpos3 , ypos3 , col , LineThicknessValue());
   al_draw_line(xpos3 , ypos3 , xpos1 , ypos1 , col , LineThicknessValue());
}



void Spiraloid::DrawOption6(double x1 , double y1 , double x2 , double y2 , ALLEGRO_COLOR col) {
   const double cx = (x1 + x2)/2.0;
   const double cy = (y1 + y2)/2.0;
   const double hx = x2 - cx;
   const double hy = y2 - cy;
   
   const double rxsv = (double)rhombus_x_scale_value;
   const double rysv = (double)rhombus_y_scale_value;

   double xpos1 = cx - (double)rysv*hx;
   double ypos1 = cy - (double)rysv*hy;
   double xpos2 = cx + (double)rysv*hx;
   double ypos2 = cy + (double)rysv*hy;
   double xpos3 = cx - (double)rxsv*hy;
   double ypos3 = cy + (double)rxsv*hx;
   double xpos4 = cx + (double)rxsv*hy;
   double ypos4 = cy - (double)rxsv*hx;

   const double rdsv = (double)rhombus_diag_scale_value;
   
   double xpos5 = cx + rdsv*(hx - hy);
   double ypos5 = cy + rdsv*(hx + hy);
   double xpos6 = cx + rdsv*(hx + hy);
   double ypos6 = cy + rdsv*(hy - hx);
   double xpos7 = cx - rdsv*(hx - hy);
   double ypos7 = cy - rdsv*(hx + hy);
   double xpos8 = cx - rdsv*(hx + hy);
   double ypos8 = cy - rdsv*(hy - hx);

   al_draw_line(xpos1 , ypos1 , xpos8 , ypos8 , col , LineThicknessValue());
   al_draw_line(xpos8 , ypos8 , xpos3 , ypos3 , col , LineThicknessValue());
   al_draw_line(xpos3 , ypos3 , xpos5 , ypos5 , col , LineThicknessValue());
   al_draw_line(xpos5 , ypos5 , xpos2 , ypos2 , col , LineThicknessValue());
   al_draw_line(xpos2 , ypos2 , xpos6 , ypos6 , col , LineThicknessValue());
   al_draw_line(xpos6 , ypos6 , xpos4 , ypos4 , col , LineThicknessValue());
   al_draw_line(xpos4 , ypos4 , xpos7 , ypos7 , col , LineThicknessValue());
   al_draw_line(xpos7 , ypos7 , xpos1 , ypos1 , col , LineThicknessValue());
}



void Spiraloid::DrawOption7(double x1 , double y1 , double x2 , double y2 , ALLEGRO_COLOR col) {
   (void)x1;
   (void)x2;
   (void)y1;
   (void)y2;
   (void)col;
}

