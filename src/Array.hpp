


#ifndef Pos2D_HPP
#define Pos2D_HPP


#include "Inline.hpp"

#include <vector>
using std::vector;

#include "Eagle/Exception.hpp"



template <class DATA_TYPE>
class Array {
   
protected :
   vector<DATA_TYPE> data_array;
///   DATA_TYPE* data_array;
   
public :
   Array();
   ~Array();
   
   DONTINLINE bool DataReady() {return data_array.size();}

   DONTINLINE unsigned int Size() {return data_array.size();}

   DONTINLINE DATA_TYPE& DataChecked(unsigned int index);

   INLINE DATA_TYPE& DataUnchecked(unsigned int index) {return data_array[index];}
   
   DATA_TYPE& Data(unsigned int index);
   

   INLINE  DATA_TYPE& operator[](unsigned int index) {return Data(index);}
   
   
   void Free();

   void Allocate(unsigned int new_size);
   
   
};




/// Because we're using a template, the code needs to be in the header, but I prefer to keep them separate
///#include "ArrayImplementation.hpp"

#endif // Pos2D_HPP

