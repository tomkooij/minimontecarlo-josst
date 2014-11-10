#include	<stdio.h>
#include	<libran.h>
#include	"main.h"

static double	*cumul_ec[CUMUL_E] = { NULL };

static double	Emin  = EMIN;
static double	Emax  = EMAX;
static double	Estep = (EMAX - EMIN) / (CUMUL_E - 1);

int process_photon( mech , Egam , x , dx )
int	mech;
double	Egam, x, dx;	{

	int	i;
	double	xi, T, rnd, random_number();

	xi = x + dx;	/* where interaction occurs */
	if( xi > THICK )	/* no interaction within scintillator */
		return 0;

	switch( mech )	{
		case PHOTO_ELECTRIC:	put_particle( ELECTRON , Egam , xi );
printf("+%2d %8.6f %8.6f %8.6f\n",PHOTO_ELECTRIC,Egam,xi,Egam);
					i = 1;
					break;
		case COMPTON:		i = do_compton( Egam , xi );
					break;
		case PAIR_CREATION:	rnd = random_number();
					if( rnd < (4.175 / 5.175) )	{
						/* Pair creation in a nuclear field */
						/* 1.022 MeV is used to create particles
						   the rest is shared */
						T = (Egam - 1.022) / 2.0;
						put_particle( ELECTRON , T , xi );
						put_particle( ELECTRON , T , xi );
printf("+%2d %8.6f %8.6f %8.6f\n",PAIR_CREATION,Egam,xi,2*T);
						i = 2;
						break;
					}
					else	{
						/* Pair creation in an electron field */
						/* 1.022 MeV is used to create particles
						   the rest is shared between newly
						   created particles and electron providing the field */
						T = (Egam - 1.022) / 3.0;
						put_particle( ELECTRON , T , xi );
						put_particle( POSITRON , T , xi );
						put_particle( ELECTRON , T , xi );
printf("+%2d %8.6f %8.6f %8.6f\n",PAIR_CREATION,Egam,xi,3*T);
						i = 3;
						break;
					}
		default:		fprintf( stderr , "Unknown mechanism %d\n" , mech );
					i = 0;
					break;
	}

	return i;

}

int do_compton( Egam , xi )
double	Egam, xi;	{

	int	i, chan, step;
	double	*ptr, edge, Eelec, T, Tstep, rnd,
		get_edge(), compelec(), random_number();

	step = (Egam - EMIN) / Estep;

	if( cumul_ec[step] == NULL )	{
		cumul_ec[step] = (double *)malloc( NCHAN * sizeof(double) );
		if( cumul_ec[step] == NULL )	{
			fprintf( stderr , "Error do_compton: not enough memory\n" );
			exit( -1 );
		}
		compelec( 1.e-3 , Egam );	/* dummy call to make sure edge is up-to-date */
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
	rnd = random_number();

	for( i=0; i<NCHAN; i++ )	{
		if( ptr[i] >= rnd )	{
			chan = i;
			break;
		}
	}

	compelec( 1.e-3 , Egam );	/* dummy call to make sure edge is up-to-date */
	edge  = get_edge();
	Eelec = (((double)chan + random_number()) / (double)NCHAN) * edge;

	put_particle( ELECTRON , Eelec , xi );
printf("+%2d %8.6f %8.6f %8.6f\n",COMPTON,Egam,xi,Eelec);
	put_particle( PHOTON , Egam-Eelec , xi );

	return 2;

}
