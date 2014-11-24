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

	/*
	Bestudeer de eigenschappen van de "gemaakte" elektronen. Worden
	ze volledig geabsorbeert in de detector of verlaten ze de detector.
	M.a.w: is alleen de diepte van interactie belangrijk of is T belangrijk?
	TK 24-11-2014
	*/

	if( x * LOSS < T ) {
		printf("T 0 %8.6f %8.6f Electron left the detector!\n", (x*LOSS), T);
		return (x * LOSS);
	} else {
		printf("T 1 %8.6f %8.6f Electron was absorbed by the detector!\n", (x*LOSS), T);
		return T;
	}
}
