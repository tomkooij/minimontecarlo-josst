#include        "libran.h"

double ran_interval( a , b )
double a, b;   {

   static double one = 1.0;
   double        x, y, z;

   x = random_number();

   if( a > b )   {
      y = b;
      z = a;
   }
   else   {
      y = a;
      z = b;
   }

   x    = min( max( ( y * ( one - x ) + z * x ) , y ) , z );

   return( x );

}
