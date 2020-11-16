


#include "Values.hpp"


#include <cmath>
#include <cstdio>

#include "Eagle/Exception.hpp"



void Value::FixDRange() {
   
   /// We know range is positive and vmin is less than vmax
   /// We can't use ival here because someone may be setting a double value
   const double power = pow(10.0 , exponent);
   const double dmin = vmin*power;
   const double dmax = vmax*power;
   const double range = (1LL + vmax - vmin)*power;
   if (vcycle) {
      if (dval < dmin) {
          dval += range*(double)(int)fmod(dmin - dval , range);
      }
      else if (dval > dmax) {
          dval -= range*(double)(int)(fmod(dval - dmax , range) + 1.0);
      }
    }
   else {
      /// Clamp values
      if (dval < dmin) {dval = dmin;}
      else if (dval > dmax) {dval = dmax;}
   }
   EAGLE_ASSERT(dval >= dmin);
   EAGLE_ASSERT(dval <= dmax);
   RefreshIValue();
}



/**
   if (dval < dmin || dval >= dmax) {
      double scale = pow(10.0 , exponent);
      int range = 1 + vmax - vmin;
      double dmax = (vmax + 1)*scale;
      double dmin = vmin*scale;
      if (vcycle) {/// perform modulus
         //dval = dmin + fmod(dval - dmin , dmax - dmin);/// *** THIS DOESN"T WORK FMOD HATES NEGATIVES
      }
      if (vcycle) {/// perform modulus
         double drange = range*scale;
         if (dval >= dmax) {
            double extra = (double)(int)((dval - dmin)/drange);
            dval -= extra*drange;
         }
         else if (ival < vmin) {
            double extra = (double)(int)((dmax - dval)/drange);
            dval += extra*drange;
         }
         EAGLE_ASSERT(dval < dmax && dval >= dmin);
      }
      else {/// clamp values
         if (dval > dmax) {dval = dmax;}
         if (dval < dmin) {dval = dmin;}
      }
      RefreshIValue();
   }
}
   */



void Value::FixIRange() {
   if (vcycle) {/// perform modulus
      long long range = 1 + vmax - vmin;
      if (ival > vmax) {
            // integer trucation
         int extra = (int)((ival - vmin)/range);
         EAGLE_ASSERT(extra);
         ival -= extra*range;
      }
      else if (ival < vmin) {
         int extra = (int)((vmax - ival)/range);
         EAGLE_ASSERT(extra);
         ival += extra*range;
      }
   }
   else {/// clamp values
      if (ival > vmax) {ival = vmax;}
      if (ival < vmin) {ival = vmin;}
   }
   RefreshDValue();
}



void Value::RefreshDValue() {
   dval = pow(10.0 , exponent)*(double)ival;
}



void Value::RefreshIValue() {
   double scale = pow(10.0 , -exponent);
   double newdval = dval*scale;
   ival = (long long)(newdval + 0.5);
///   printf("Value::RefreshIValue - newdval == %12.16lf , newival == %d\n" , newdval , (int)ival);
}



Value::Value() :
      dval(0.0),
      ival(0),
      vmin(0),
      vmax(0),
      vcycle(false),
      exponent(0)
{}



void Value::SetValues(long long valuemin , long long value , long long valuemax , int power_of_ten , bool cycle) {
   if (valuemin > valuemax) {
      long long temp = valuemax;
      valuemax = valuemin;
      valuemin = temp;
   }
   vmin = valuemin;
   vmax = valuemax;
   ival = value;
   exponent = power_of_ten;
   vcycle = cycle;

   FixIRange();
}



void Value::SetValue(long long value) {
   ival = value;
   FixIRange();
}



void Value::SetValue(int value) {
   SetValue((long long)value);
}




void Value::SetValue(double value) {
   dval = value;
   FixDRange();
}
   


void Value::Increment(int value , int power_of_ten) {
   while (exponent < power_of_ten) {
      --power_of_ten;
      value *= 10;
   }
   while (exponent > power_of_ten) {
      --exponent;
      ival *= 10;
      vmin *= 10;
      vmax *= 10;
   }
///   printf("Before incrementing ival and calling FixIRange, ival == %d , value == %d\n" , (int)ival , value);
   ival += value;
   FixIRange();
///   printf("After incrementing ival and calling FixIRange, ival == %d\n" , (int)ival);
}



void Value::Decrement(int value , int power_of_ten) {
   Increment(-value , power_of_ten);
}



void Value::Increment(int value) {
   Increment(value , exponent);
}



void Value::Decrement(int value) {
   Decrement(value , exponent);
}



void Value::Increment(double value) {
   dval += value;
   FixDRange();
}



void Value::Decrement(double value) {
   Increment(-value);
}



Value::operator int() {
   return (int)IVal();
}



Value::operator float() {
   return (float)dval;
}



Value::operator double() {
   return dval;
}


/*
Value::operator long long() {
   return ival;
}
*/


Value& Value::operator=(long long value) {
   SetValue(value);
   return *this;
}



Value& Value::operator=(int value) {
   SetValue(value);
   return *this;
}



Value& Value::operator=(double value) {
   SetValue(value);
   return *this;
}



void Value::operator+=(int value) {
   Increment(value);
}



void Value::operator-=(int value) {
   Increment(-value);
}



void Value::operator+=(double value) {
   Increment(value);
}



void Value::operator-=(double value) {
   Increment(-value);
}
   


Value& Value::operator++(int) {
   Increment(1,exponent);
   return *this;
}



Value& Value::operator--(int) {
   Decrement(1,exponent);
   return *this;
}



Value& Value::operator++() {
   Increment(1,exponent);
   return *this;
}



Value& Value::operator--() {
   Decrement(1,exponent);
   return *this;
}


