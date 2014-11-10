#include	<time.h>
#include        "libran.h"

void ran_random()   {

   long			ia, ib, ipw2a, j, init, fd;
   static long		ilim =     4,
			ipw2 = 32768;
   extern BLOCKA        a_block;
   extern BLOCKB        b_block;

   ini_random( &init );

   fd    = open( "/dev/random" );
   read( fd , &ia , sizeof(long) );
   close( fd );
   ia    = abs( ia );
   ipw2a = ipw2 >> 2;
   ib    = ia / ipw2a;

   a_block.b[0] = ( ( ia - ipw2a * ib ) << 2 ) + 2;
   for ( j = 1; j < ilim; j++ )   {
      ia           = ib;
      ib           = ia / ipw2;
      a_block.b[j] = ia - ipw2 * ib;
   }

   b_block.normal =  1.0;
   b_block.gamma  = -1.0;

   random_number();

}
