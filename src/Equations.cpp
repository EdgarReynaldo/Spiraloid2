




#include "Equations.hpp"

#include <cmath>


Pos2D SpiralEquation2D::Evaluate(double theta) {
   /// R(theta) = radial_delta*(theta/2.0PI);
   const double radian_percent = theta/360.0;
   const double radians = radian_percent*2.0*M_PI;
   const double radius = radial_delta*radian_percent;
   Pos2D p;
   p.tx = radius*cos(radians);
   p.ty = radius*sin(radians);
   return p;
}

