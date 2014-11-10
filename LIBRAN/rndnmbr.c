#include        "libran.h"

double random_number()   {

   static double        rpw2a = 9.313225746154785156e-10,
                        rpw2b = 1.110223024625156540e-16,
                        delta = 2.775557561562891351e-17;

   static long		init = TRUE;
   static long		m[4] = { 17917 , 13895 , 19930 , 8 }, t[4];
   double               x;
   extern BLOCKA        a_block;

   if( init == TRUE )   ini_random( &init );

   t[0] = a_block.b[0] * m[0];
   t[1] = ( t[0] >> 15 ) + a_block.b[1] * m[0] + a_block.b[0] * m[1];
   t[2] = ( t[1] >> 15 ) + a_block.b[2] * m[0] + a_block.b[1] * m[1] + a_block.b[0] * m[2];
   t[3] = ( t[2] >> 15 ) + a_block.b[3] * m[0] + a_block.b[2] * m[1] + a_block.b[1] * m[2] + a_block.b[0] * m[3];

   a_block.b[3] = t[3] & 32767;
   a_block.b[2] = t[2] & 32767;
   a_block.b[1] = t[1] & 32767;
   a_block.b[0] = t[0] & 32767;

   x = rpw2a * (double)( ( a_block.b[3] << 15 ) + a_block.b[2] )
       + rpw2b * (double)( ( a_block.b[1] << 8 ) + ( a_block.b[0] >> 7 ) )
       + delta;

   return( x );

}
