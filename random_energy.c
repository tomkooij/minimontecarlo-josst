/*

This is not used!
(TK)


*/

#include	<stdio.h>
#include	<libran.h>
#include	"main.h"

static double	*cumul_ec[CUMUL_E] = { NULL };

static double	Emin  = EMIN;
static double	Emax  = EMAX;
static double	Estep = (EMAX - EMIN) / (CUMUL_E - 1);

double random_energy( Egam , mech )
double	Egam;
int	mech;	{

	int	i, chan, step;
	double	x, *ptr, edge, Eelec, T, Tstep,
		get_edge(), compelec(), random_number();

if( mech == PHOTO_ELECTRIC )	{
	return Egam;
}

if( mech == PAIR_CREATION )	{
	x = random_number();
	if( x < (4.175 / 5.175) )	{
		/* Pair creation in a nuclear field */
		return THICK * LOSS * 2;
	}
	else	{
		/* Pair creation in an electron field */
		return THICK * LOSS * 3;
	}
}

if( mech == COMPTON )	{
	step = (Egam - EMIN) / Estep;

	if( cumul_ec[step] == NULL )	{
		cumul_ec[step] = (double *)malloc( NCHAN * sizeof(double) );
		if( cumul_ec[step] == NULL )	{
			fprintf( stderr , "Error random_energy: not enough memory\n" );
			exit( -1 );
		}
		compelec( 1.0 , Egam );
		edge  = get_edge();
		ptr   = cumul_ec[step];
		Tstep = edge / NCHAN;
/* dsigma/dT */
		for( i=0; i<NCHAN; i++ )	{
			T      = (Tstep - 1.0e-3) + i * Tstep;
			ptr[i] = compelec( T , Egam );
		}
/* sigma(x<T) */
		for( i=1; i<NCHAN; i++ )
			ptr[i] = ptr[i] + ptr[i-1];
/* normalize */
		for( i=0; i<NCHAN; i++ )
			ptr[i] = ptr[i] / ptr[NCHAN-1];
	}

	ptr = cumul_ec[step];
	x   = random_number();

	for( i=0; i<NCHAN; i++ )	{
		if( ptr[i] >= x )	{
			chan = i;
			break;
		}
	}

	compelec( 1.0 , Egam );
	edge  = get_edge();
	Eelec = (((double)chan + random_number()) / (double)NCHAN) * edge;

	return Eelec;
}

}
