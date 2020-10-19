

#include "Array.hpp"
#include "Eagle/Position.hpp"


#include "allegro5/allegro.h"

#include "Eagle/StringWork.hpp"


///Array<ALLEGRO_COLOR> fake_array;


template <class DATA_TYPE>
Array<DATA_TYPE>::Array() :
      data_array()
{
   
}



template <class DATA_TYPE>
Array<DATA_TYPE>::~Array()
{
   Free();
}



template <class DATA_TYPE>
DATA_TYPE& Array<DATA_TYPE>::DataChecked(unsigned int index) {
   if (index >= data_array.size()) {
      throw EagleException(StringPrintF("Array<DATA_TYPE>::DataChecked() - index %u out of bounds (%u)\n" , index , data_array.size()));
   }
   return DataUnchecked(index);
}



template <class DATA_TYPE>
DATA_TYPE& Array<DATA_TYPE>::Data(unsigned int index) {
   #ifdef DEBUG
      return DataChecked(index);
   #else
      return DataUnchecked(index);
   #endif // DEBUG
}



template <class DATA_TYPE>
void Array<DATA_TYPE>::Free() {data_array.clear();}



template <class DATA_TYPE>
void Array<DATA_TYPE>::Allocate(unsigned int new_size) {
   data_array.resize(new_size);
}



Array<ALLEGRO_COLOR> fake_array;

template class Array<ALLEGRO_COLOR>;
template class Array<Pos2D>;
///void Array<ALLEGRO_COLOR>::Allocate(unsigned int new_size);




