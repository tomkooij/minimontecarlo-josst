#include	<stdio.h>
#include	<libran.h>
#include	"main.h"

double process_electron( T , xi )
double	T, xi;	{

	int	i, chan, step;
	double	x;

	/* electron with kinetic energy T, created xi cm below surface 
		assumed is: electrons remain on path vertically down */

	x = THICK - xi;		/* length remaining in scintillator */

	if( x * LOSS < T )
		return (x * LOSS);
	else
		return T;

}
