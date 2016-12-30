#include <stdlib.h>
#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_cdf.h>
#include <math.h>
#include <time.h>

double price(
  char call_put_flag,
  double s, // price of underlier
  double k, // strike
  double r, // risk free rate
  double v, // volatility
  double t, // time to maturity
  double d // discount rate
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

  switch( call_put_flag ) {
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

  double call_price = price( 'c', s, k, r, v, t, d );
  double put_price = price( 'p', s, k, r, v, t, d );

  printf("{\n  call: %f, \n  put: %f\n}\n", call_price, put_price);

  return 0;

}
