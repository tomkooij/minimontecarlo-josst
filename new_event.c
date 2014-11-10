#include	<stdio.h>
#include	<math.h>
#include	<libran.h>
#include	"main.h"

#undef		EXPE
#undef		CONSTE
#define		INVE		(0.1)

typedef struct particlelist	{
	double	E;
	double	x;
	int	pid;
	int	used;
}	P_LIST;

static P_LIST	particles[NPARTICLES];
static int	current = -1;
static int	valid   = 0;

void print_version( Egam )
double	Egam;	{

#ifdef CONSTE
	fprintf( stderr , "Incoming energy: constant %.3f MeV\n" , Egam );
#endif
#ifdef EXPE
	fprintf( stderr , "Incoming energy: distributed as exp(-E/%.3f)\n" , Egam );
#endif
#ifdef INVE
	fprintf( stderr , "Incoming energy: distributed as 1/E (%.3f<E<%.3f MeV)\n" , INVE , Egam );
#endif
	fprintf( stderr , "Current energy | mechanism | loc interaction | energy lost\n" );

}

double new_event( Egam )
double	Egam;	{

	double	Ecur, x, ran_interval();

#ifdef	CONSTE	/* constant incoming energy */
	Ecur  = Egam;
#endif
#ifdef	EXPE	/* incoming energy distributed as exp(-E/Egam) */
	x     = ran_interval( 0.0 , 0.999 );
	Ecur  = -1.0 * abs( Egam ) * log( x );
#endif
#ifdef	INVE	/* incoming energy distributed as 1/E */
	x     = ran_interval( 0.0 , log( Egam/INVE ) ); /* INVE<Ecur<Egam */
	Ecur  = INVE * exp( x );
#endif

	valid   = 1;
	current = 0;

	memset( particles , 0 , 10*sizeof( P_LIST ) );
	particles[0].E    = Ecur;
	particles[0].x    = 0.0;
	particles[0].pid  = PHOTON;
	particles[0].used = 0;

	return Ecur;

}

int put_particle( pid , energy , location )
int	pid;
double	energy, location;	{

	int	i;

	particles[valid].E    = energy;
	particles[valid].x    = location;
	particles[valid].pid  = pid;
	particles[valid].used = 0;
	valid++;

if(valid>NPARTICLES)	{
fprintf(stderr,"ERROR: put_particle: stack overflow! Current stack:\n");
for(i=0;i<NPARTICLES;i++)
fprintf(stderr,"%f %f %d %d\n",particles[i].E,particles[i].x,particles[i].pid,particles[i].used);
fprintf(stderr,"new: %f %f %d\n",energy,location,pid);
exit(-1);
}

	return valid;

}

int get_particle( pid , energy , location )
int	*pid;
double	*energy, *location;	{

	if( current < valid )	{

		if( particles[current].used == 1 )	{
			fprintf( stderr , "Trying to retrieve used data (current, valid %d,%d)\n", current , valid );
			exit( -1 );
		}
		*energy   = particles[current].E;
		*location = particles[current].x;
		*pid      = particles[current].pid;
		particles[current].used = 1;
		current++;
		return 1;
	}

	return 0;

}
