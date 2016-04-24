


#ifndef Equations_HPP
#define Equations_HPP

#include "Position.hpp"



class Equation2D {
public :
   virtual ~Equation2D() {}
   virtual Pos2D Evaluate(double input)=0;
};



class PolarEquation2D : public Equation2D {
   
public :
///   R(theta) = theta;
   virtual ~PolarEquation2D() {}
   virtual Pos2D Evaluate(double theta)=0;
   
};

class SpiralEquation2D : public PolarEquation2D {
   
public :
   virtual ~SpiralEquation2D() {}
   double radial_delta;

   SpiralEquation2D() : radial_delta(1.0) {}
   
   Pos2D Evaluate(double theta);/// theta is in degrees
   
};





#endif // Equations_HPP

