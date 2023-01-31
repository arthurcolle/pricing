#include <stdlib.h>
#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_cdf.h>
#include <math.h>
#include <time.h>

// Function to compute the option price
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

// Function to compute the option greeks
void greeks(
  char call_put_flag,
  double s, // price of underlier
  double k, // strike
  double r, // risk free rate
  double v, // volatility
  double t, // time to maturity
  double d, // discount rate
  double *delta, // delta
  double *gamma, // gamma
  double *vega,  // vega
  double *theta, // theta
  double *rho    // rho
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

  // Compute the option price
  switch( call_put_flag ) {
    case 'c':
      price = ( s * exp_dt * gsl_cdf_ugaussian_P( d1 ) ) -
              ( k * exp_rt * gsl_cdf_ugaussian_P(d2 ) );
      break;
    case 'p':
      price = ( k * exp_rt * gsl_cdf_ugaussian_P( -d2 ) ) -
              ( s * exp_dt * gsl_cdf_ugaussian_P( -d1 ) );
    break;
  default:
    printf( "Unacceptable option type.\nPlease specify 'c' or 'p'.\n" );
  }

  // Compute the option greeks
  *delta = ( call_put_flag == 'c' ) ? exp_dt * gsl_cdf_ugaussian_P( d1 ) : -exp_dt * gsl_cdf_ugaussian_P( -d1 );
  *gamma = ( exp_dt / ( s * vsqrt_t ) ) * gsl_ran_ugaussian_pdf( d1 );
  *vega = s * sqrt_t * exp_dt * gsl_ran_ugaussian_pdf( d1 );
  *theta = ( ( -( s * v * exp_dt * gsl_ran_ugaussian_pdf( d1 ) ) ) / ( 2 * sqrt_t ) ) -
           ( r * k * exp_rt * gsl_cdf_ugaussian_P( ( call_put_flag == 'c' ) ? d2 : -d2 ) );
  *rho = ( k * t * exp_rt * gsl_cdf_ugaussian_P( ( call_put_flag == 'c' ) ? d2 : -d2 ) );
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

  // Compute the option greeks for the call option
  double call_delta, call_gamma, call_vega, call_theta, call_rho;
  greeks( 'c', s, k, r, v, t, d, &call_delta, &call_gamma, &call_vega, &call_theta, &call_rho );
  // Compute the option greeks for the put option
  double put_delta, put_gamma, put_vega, put_theta, put_rho;
  greeks( 'p', s, k, r, v, t, d, &put_delta, &put_gamma, &put_vega, &put_theta, &put_rho );

  printf( "{\"call\": %f, \"put\": %f, \"call_delta\": %f, \"call_gamma\": %f, \"call_vega\": %f, \"call_theta\": %f, \"call_rho\": %f, \"put_delta\": %f, \"put_gamma\": %f, \"put_vega\": %f, \"put_theta\": %f, \"put_rho\": %f}\n",
          call_price, put_price, call_delta, call_gamma, call_vega, call_theta, call_rho, put_delta, put_gamma, put_vega, put_theta, put_rho );

  return 0;
}

