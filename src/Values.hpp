




#ifndef Values_HPP
#define Values_HPP


class Value {
   
private :
   double dval;
   long long ival;
   
   long long vmin;
   long long vmax;
   bool vcycle;/// Whether or not to cycle values
   
   int exponent;/// dval = ival*10^exp

   void FixDRange();
   void FixIRange();
   void RefreshDValue();
   void RefreshIValue();
   
public :
   Value() :
         dval(0.0),
         ival(0),
         vmin(0),
         vmax(0),
         vcycle(false),
         exponent(0)
   {}
   
   void SetValues(long long valuemin , long long value , long long valuemax , int power_of_ten , bool cycle = false);
   void SetValue(long long value);
   void SetValue(int value);
   void SetValue(double value);

   void Increment(int value , int power_of_ten);
   void Decrement(int value , int power_of_ten);
   void Increment(int value);
   void Decrement(int value);
   void Increment(double value);
   void Decrement(double value);
   
   int Exponent() {return exponent;}
   
   operator int();
   operator double();
   long long IVal() {return ival;}

   Value& operator=(long long value);
   Value& operator=(int value);
   Value& operator=(double value);
   
   void operator+=(int value);
   void operator-=(int value);
   void operator+=(double value);
   void operator-=(double value);

   
   
};


#endif // Values_HPP

