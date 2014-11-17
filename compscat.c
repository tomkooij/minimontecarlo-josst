/*
Not used! (TK)
/*

#include	<stdio.h>
#include	<math.h>

#define		ELECTR_DENS	(3.37e23)	/* scintillator material */

/*	switch opt
	opt=0	function calculates cross-section for Compton scattering
	opt=1	calculates scattered photon
	opt=-1	calculates scattered electron
*/

static int	opt = 0;

int put_opt( n )
int	n;	{

	opt = n;

	return opt;

}

double	compscat( Egam )
double	Egam;	{

	double	Me, re, kinfac, A, B, C, D, E, F, gam, sigma, sigmas, sigmac;

/*	All energies in MeV; distances in cm	*/


	/* Ref: Leo, 1987
			chap 2.7, p. 52
			*/

	Me     = 0.510998902;
	re     = 2.817940285e-13;
	kinfac = 2.0 * M_PI * (re * re);

	gam = Egam / Me;
	A   = (1.0 + gam) / (gam * gam);
	B   = 1.0 + 2.0 * gam;
	C   = 2.0 *(1.0 + gam) / B;
	D   = log( B ) / gam;
	E   = 2.0 * (1.0 + gam) * (2.0 * gam * gam - 2.0 * gam - 1.0);
	E   = E / ((gam * gam) * (B * B));
	F   = 8.0 * gam * gam / (3.0 * B * B);

	sigmac = kinfac * (A * (C - D) + 0.5 * D - (1.0 + 3.0 * gam) / (B * B));

	sigmas = (kinfac / 2.0) * (D / (gam * gam) + E + F);

	sigma  = sigmac - sigmas;

	switch( opt )	{
		case 0:		return sigmac;
		case 1:		return sigmas;
		case -1:	return sigma;
	}

	return 0.0;

}

double compfree( Egam )
double	Egam;	{

	int	i;
	double	free, compscat();

	free = compscat( Egam ) * ELECTR_DENS;

	return (1.0 / free);

}
