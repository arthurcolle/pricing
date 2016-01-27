#include <stdlib.h>
#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_cdf.h>
#include <math.h>
#include <time.h>

// uint64_t ts() {
//     struct timeval tv;
//     gettimeofday(&tv,NULL);
//     return tv.tv_sec*(uint64_t)1000000+tv.tv_usec;
// }

static unsigned long long ts2() {
    unsigned int eax, edx;
    unsigned long long val;
    __asm__ __volatile__("rdtsc":"=a"(eax), "=d"(edx));
    val = edx;
    val = val << 32;
    val += eax;
    return val;
}

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
  double call_price = price( 'c', s, k, r, v, t, d );
  double put_price = price( 'p', s, k, r, v, t, d );

  printf( "{s: %f,", s ); // underlier
  printf( "k: %f,", k ); // strike price
  printf( "r: %f,", r ); // risk free rate
  printf( "t: %f,", t ); // time to expiry
  printf( "v: %f,", v ); // vol 
  printf( "d: %f,", d ); // dividend yield   
  printf("prices: [\"c\":%f, \"p\":%f]}\n", call_price, put_price);
  // long long unsigned int start;
  // long long unsigned int start2;
  // long long unsigned int end;
  // long long unsigned int end2;

  

  

  return 0;

}

