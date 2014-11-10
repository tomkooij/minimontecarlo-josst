#include	<stdio.h>
#include	<sys/timeb.h>
#include	"libran.h"

#define		MAX_LOOP	100

main()	{

	long		i, k;
	double		a, b, x, empty, full, result[4];
	struct timeb	strt, stp;

	a = 0.37;
	b = 0.16;
	k = 0;

	ran_random();

	ftime( &strt );
	for( i=0L; i<(MAX_LOOP*1000L); i++ )
		x = a;
	ftime( &stp );

	empty = (double)(stp.time - strt.time);
	if( stp.millitm >= strt.millitm )
		empty += (double)(stp.millitm - strt.millitm) / 1000.0;
	else
		empty += ((double)(1000 + stp.millitm - strt.millitm) / 1000.0) - 1.0;

	printf( "Empty loop takes                                         : %.3f sec\n" , empty );

	ftime( &strt );
	for( i=0L; i<(MAX_LOOP*1000L); i++ )
		x = random_number();
	ftime( &stp );

	full = (double)(stp.time - strt.time);
	if( stp.millitm >= strt.millitm )
		full += (double)(stp.millitm - strt.millitm) / 1000.0;
	else
		full += ((double)(1000 + stp.millitm - strt.millitm) / 1000.0) - 1.0;

	printf( "Loop with %ldk random numbers takes                      : %.3f sec\n" , i/1000 , full );
	result[k++] = (full - empty) / (double)i;

	ftime( &strt );
	for( i=0L; i<(MAX_LOOP*1000L); i++ )
		x = ran_interval( a , b );
	ftime( &stp );

	full = (double)(stp.time - strt.time);
	if( stp.millitm >= strt.millitm )
		full += (double)(stp.millitm - strt.millitm) / 1000.0;
	else
		full += ((double)(1000 + stp.millitm - strt.millitm) / 1000.0) - 1.0;

	printf( "Loop with %ldk random intervals takes                    : %.3f sec\n" , i/1000 , full );
	result[k++] = (full - empty) / (double)i;

	ftime( &strt );
	for( i=0L; i<(MAX_LOOP*1000L); i++ )
		x = ran_exp_distr( a );
	ftime( &stp );

	full = (double)(stp.time - strt.time);
	if( stp.millitm >= strt.millitm )
		full += (double)(stp.millitm - strt.millitm) / 1000.0;
	else
		full += ((double)(1000 + stp.millitm - strt.millitm) / 1000.0) - 1.0;

	printf( "Loop with %ldk random numbers (exp. distribution) takes  : %.3f sec\n" , i/1000 , full );
	result[k++] = (full - empty) / (double)i;

	ftime( &strt );
	for( i=0L; i<(MAX_LOOP*1000L); i++ )
		x = ran_norm_distr( a , b );
	ftime( &stp );

	full = (double)(stp.time - strt.time);
	if( stp.millitm >= strt.millitm )
		full += (double)(stp.millitm - strt.millitm) / 1000.0;
	else
		full += ((double)(1000 + stp.millitm - strt.millitm) / 1000.0) - 1.0;

	printf( "Loop with %ldk random numbers (normal distribution) takes: %.3f sec\n" , i/1000 , full );
	result[k++] = (full - empty) / (double)i;

	printf( "\n\nRESULTS:\n========\n\n" );
	printf( "1 random number in                : %.1f usec\n" , result[0]*1000000.0 );
	printf( "1 random interval in              : %.1f usec\n" , result[1]*1000000.0 );
	printf( "1 random number (exp. distr.) in  : %.1f usec\n" , result[2]*1000000.0 );
	printf( "1 random number (normal distr.) in: %.1f usec\n" , result[3]*1000000.0 );

}
