#include	<stdio.h>
#include	<libran.h>
#include	"main.h"

static double	free;		/* cm */
static int	mechanism = NOT_DEFINED;

int	get_mechanism()	{

	return mechanism;

}

double	get_free()	{

	return free;

}

double next_interaction( Egam )
double	Egam;	{

	int	i, m;
	double	x[NMECHANISMS], y[NMECHANISMS], xmin,
		compscat(), compfree(), pefree();

	y[0] = pefree( Egam );
	x[0] = ran_exp_distr( y[0] );

	y[1] = compfree( Egam );
	x[1] = ran_exp_distr( y[1] );

	y[2] = 9.0 * LRAD / 7.0;
	x[2] = ran_exp_distr( y[2] );

	xmin = x[0];
	free = y[0];
	m    = 0;

	for( i=1; i<NMECHANISMS; i++ )	{
		if( (i == PAIR_CREATION) && (Egam < 2.044) )
			continue;
		if( xmin < x[i] )
			continue;
		xmin = x[i];
		free = y[i];
		m    = i;
	}
printf( "#%d %.3f %.3f %.3f %.3f %.3f %.3f\n" , m ,
	y[0] , y[1] , y[2] , x[0] , x[1] , x[2] );

	mechanism = m;

	return xmin;

}
