#ifndef	TRUE
#define         TRUE            1
#endif

#ifndef	FALSE
#define         FALSE           0
#endif

#ifndef abs
#define         abs(x)          ((x)<0?-(x):(x))
#endif

#ifndef min
#define         min(x,y)        ((x)<=(y)?(x):(y))
#endif

#ifndef	max
#define         max(x,y)        ((x)>(y)?(x):(y))
#endif

typedef struct blocka   {
      long	b[4];
      long	option;
      long	possop;
      long	defopt;
}   BLOCKA;

typedef struct blockb   {
      double	normal;
      double	gamma;
}   BLOCKB;

void	ini_random( long *init );
void	ran_random( void );
void	ran_set( int i );
double	ran_interval( double a, double b );
double	ran_exp_distr( double a );
double	ran_norm_distr( double a, double b );
double	random_number( void );
