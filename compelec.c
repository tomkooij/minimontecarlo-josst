#include	<stdio.h>
#include	<math.h>

static double	edge;

double get_edge()	{

	return edge;

}

double compelec( T , Egam )
double	T, Egam;	{

	double	Me, re, A, B, C, D, s, sigma, gam, kinfac;

/* 	energies in MeV; distances in cm;	 */

	Me = 0.510998902;
	re = 2.817940285e-13;

	gam  = (Egam / Me);
	A    = (1.0 + 2.0 * gam);
	edge = (Egam * 2.0 * gam / A);
	if( T > edge )
   		return 0.0;

	kinfac = M_PI * (re * re) / Me / (gam * gam);

	s = T / Egam;
	B = 1.0  -  s;
	C = (s * s) / (gam * gam) / (B * B);
	D = (s / B) * (s - 2.0 / gam);

	sigma = kinfac * (2.0 + C + D);

	return sigma;

}
