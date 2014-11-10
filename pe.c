#include	<stdio.h>
#include	<math.h>

/*	PHOTO-ELECTRIC EFFECT	*/

#define		ELECTR_DENS	(3.37e23)	/* scintillator material */

double pefree( Egam )				/* Egam in MeV */
double	Egam;	{

	int	i;
	double	free;				/* cm */

	free = 1.4921e6 * pow( Egam , 3.2095 );	/* fit on NIST data */

	return free;

}
