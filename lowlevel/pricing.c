#include <stdlib.h>
#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_cdf.h>
#include <math.h>

double price(
	char cp_flag,
	double s, 
	double k, 
	double r,
	double v,
	double t, 
	double d
)
{
	double sqrt_t = sqrt( t ),
	       rt = ( r * t ),
	       vsqrt_t = ( v * sqrt_t ),
	       d1 = ( ( log( s / k ) + rt ) / vsqrt_t ),
	       d2 = d1 - vsqrt_t,
	       dt = ( d * t ),
	       exp_dt = exp( -dt ),
	       exp_rt = exp( -rt ),
	       price = 0;

	switch( cp_flag ) {
		case 'c': 
			price = ( s * exp_dt * gsl_cdf_ugaussian_P( d1 ) ) -
							( k * exp_rt * gsl_cdf_ugaussian_P( d2 ) );
			break;
		case 'p': 
			price = ( k * exp_rt * gsl_cdf_ugaussian_P( -d2 ) ) -
							( s * exp_dt * gsl_cdf_ugaussian_P( -d1 ) );
			break;
		default:
			printf( "Unacceptable option type.\nPlease specify 'c' or 'p'.\n" );
	}
	return price;
}


int main ( int argc, char *argv[] )
{
	// 
  double underlier_price = atof( argv[1] );
  double s = underlier_price;

  double strike_price = atof( argv[2] );
  double k = strike_price;

  double risk_free_rate = atof( argv[3] );
  double r = risk_free_rate;

  double time_to_maturity = atof( argv[4] );
  double t = time_to_maturity;

  double underlier_volatility = atof( argv[5] );
  double v = underlier_volatility;

  double discount_rate = atof( argv[6] );
  double d = discount_rate;

  printf( "Underlier price (u): %f\n", s );
  printf( "   Strike price (s): %f\n", k );
  printf( " risk free rate (r): %0.05f\n", r ); 
  printf( " Time to expiry (t): %0.05f\n", t );
  printf( "     Volatility (v): %0.05f\n", v );
  printf( " Dividend yield (d): %0.05f\n", d );
  printf( "\n" );
  printf( "price call: %f\n", price( 'c', s, k, r, v, t, d ) );
  printf( "price  put: %f\n", price( 'p', s, k, r, v, t, d ) );
  return 0;
}

