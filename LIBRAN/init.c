#include        "libran.h"

BLOCKA          a_block;
BLOCKB          b_block;

void ini_random( init )
long	*init;   {

   static long		init2 = TRUE;
   extern BLOCKA	a_block;
   extern BLOCKB	b_block;

   if( init2 == TRUE )   {

      a_block.b[0]   = 6698;
      a_block.b[1]   = 7535;
      a_block.b[2]   = 26792;
      a_block.b[3]   = 30140;

      a_block.option = 0;
      a_block.defopt = 0;
      a_block.possop = 0;

      b_block.normal =  1.0;
      b_block.gamma  = -1.0;

      init2           = FALSE;

   }

   *init        = FALSE;

}
