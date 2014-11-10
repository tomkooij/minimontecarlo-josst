#include	<math.h>
#include        "libran.h"

double ran_exp_distr( a )
double a;   {

   double    x;
   double    log();

   x = random_number();
   x = -1.0 * abs( a ) * log( x );

   return( x );

}
