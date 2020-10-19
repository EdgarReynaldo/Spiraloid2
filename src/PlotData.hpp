


#ifndef PlotData_HPP
#define PlotData_HPP



#include "Equations.hpp"

///class Equation2D;


class Plot {
   
public :
   virtual ~Plot() {}
      
   virtual void GeneratePlotData()=0;
   virtual void Draw()=0;
};


#endif // PlotData_HPP



