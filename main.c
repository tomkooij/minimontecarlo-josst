#include	<stdio.h>
#include	<stdlib.h>
#include	<getopt.h>
#include	<libran.h>
#include	<math.h>
#include	"main.h"

void usage( name )
char	*name;	{

	fprintf( stderr , "Usage: %s [-h] [-s n] [-n #] [-e Egam]\n" , name );
	fprintf( stderr , "       no -s option: random seed\n" );
	fprintf( stderr , "       -s 0: default (fixed) seed\n" );
	fprintf( stderr , "       -s n: initial seed is set at n\n" );
	fprintf( stderr , "       -n:   number of electrons to be generated\n" );
	fprintf( stderr , "       -e:   gamma energy [MeV]\n" );
	fprintf( stderr , "       -h:   print this information\n" );


}

main( argc , argv )
int	argc;
char	*argv[];	{

	int		i, j, k, n, pid, nevt, mech, opt;
	long		seed;
	double		Egam, Ecur, Eloss, dE, x, dx, Eprim,
			next_interaction(), new_event(), process_electron();
	char		*ptr;

	seed   = -1;
	nevt   = 10000;
	Egam   = 10.0;

	while( (opt = getopt( argc , argv , "he:n:s:" )) != EOF )	{
		switch( opt )	{
			case 'e':	Egam = strtod( optarg , &ptr );
					if( ptr == optarg )     {
						fprintf( stderr , "Argument to the -e option not a valid number\n" );
						exit( -1 );
					}
					break;
			case 'n':	nevt = strtol( optarg , &ptr , 0 );
					if( ptr == optarg )     {
						fprintf( stderr , "Argument to the -n option not a valid number\n" );
						exit( -1 );
					}
					break;
			case 's':	seed = strtol( optarg , &ptr , 0 );
					if( ptr == optarg )     {
						fprintf( stderr , "Argument to the -s option not a valid number\n" );
						exit( -1 );
					}
					if( seed == 0 )
						ini_random( &seed );
					else
						ran_set( seed );
					break;
			case 'h':	usage( argv[0] );
					exit( 0 );
			default:	usage( argv[0] );
					exit( 1 );
		}
	}

	print_version();

	if( seed < 0 )
		ran_random();

	n = 0;
	i = 0;

	put_opt( 0 );	/* calculate Compton scattering cross-section */

	while( n < nevt )	{
		i++;
		Eloss = 0.0;
		Eprim = new_event( Egam );	/* create new 'primary' photon */

		do	{
			k     = get_particle( &pid , &Ecur , &x );	/* take it from stack */
			if( k == 0 )		/* no more particles */
				break;

			if( x > THICK )	{	/* should never be the case */
				fprintf( stderr , "ERROR: outside scintillator\n" );
				exit( -1 );
			}

			switch( pid )	{
				case PHOTON:	dx   = next_interaction( Ecur );
						mech = get_mechanism();
						k    = process_photon( mech , Ecur , x , dx );
						dE   = 0.0;
						break;
				case ELECTRON:	dE = process_electron( Ecur , x );
						break;
				default:	fprintf( stderr , "Unknown particle %d\n" , pid );
						dE   = 0;
						break;
			}

			Eloss = Eloss + dE;

		}	while( 1 );

		if( Eloss > 0.0 )	{
			printf( "%f %d %f %f\n" , Eprim , mech , x , Eloss );
			n++;
		}
 	}

	fprintf( stderr , "detected, generated: %d %d\n" , n , i );

}
