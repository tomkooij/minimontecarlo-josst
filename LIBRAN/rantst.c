#include	<stdio.h>
#include	<math.h>
#include	<signal.h>

int	Stop = 0;

void Control_C()	{

	signal( SIGINT , Control_C );
	signal( SIGTERM , Control_C );
	signal( SIGKILL , Control_C );
	signal( SIGHUP , Control_C );

	Stop = 1;

}

#define		FWHM			(5.0)
#define		SIGWID			(FWHM/2.35)
#define		NO_POINTS		(256)

main()	{

	int	i, k;
	long	obs[512];
	double	r, x, y, random_number(), ran_norm_distr();

	for( i=0; i<512; i++ )
		obs[i] = 0;

	signal( SIGINT , Control_C );
	signal( SIGTERM , Control_C );
	signal( SIGKILL , Control_C );
	signal( SIGHUP , Control_C );

	for( i=0; i<100000; i++ )	{
		x = ran_norm_distr( 0.0 , SIGWID );
		y = ran_norm_distr( 0.0 , SIGWID );
		r = sqrt( x * x + y * y );
		k = (int)(20.0 * r);
		if( (k >= 0) && (k < 512) )
			obs[k]++;
		if( Stop )
			break;
	}

	x = y = 0.0;
	for( k=0; k<512; k++ )	{
		x = x + (double)obs[k] * (double)(k)/20.0;
		y = y + (double)obs[k] * (double)(k) * (double)(k) / 400.0;
	}
	x = x / (double)i;
	y = y / (double)i;
	y = sqrt( y - x * x );

	fprintf( stderr , "After %6d series:\nMean observed difference %.3f , sigma therein %.3f\n" , i , x , y );

	printf( "\nObserved:\n\n" );
	for( i=0; i<512; i++ )
		printf( "%.6f	%ld\n" , ((double)(i)/20.0) , obs[i] );

}
