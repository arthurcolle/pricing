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

  printf( "Underlier price (u): %f\n", s );
  printf( "   Strike price (s): %f\n", k );
  printf( " risk free rate (r):   %8f\n", r ); 
  printf( " Time to expiry (t):   %8f\n", t );
  printf( "     Volatility (v):   %8f\n", v );
  printf( " Dividend yield (d):   %8f\n", d );
  printf( "\n" );
  long long unsigned int start;
  long long unsigned int start2;
  long long unsigned int end;
  long long unsigned int end2;
  
  start = ts2();
  printf("start time: %llu\n", start);
  double call_price = price( 'c', s, k, r, v, t, d );
  end = ts2();
  printf("end time: %llu\n", end);
  
  printf( "price call: %f\n",  call_price );
 

  start2 = ts2();
printf("start2 time: %llu\n", start2);
  
  double put_price = price( 'p', s, k, r, v, t, d );
  end2 = ts2();
  printf("end2 time: %llu\n", end2);

  printf( "price  put: %f\n", put_price );

  long long unsigned int call_calc_time = end-start;
  long long unsigned int put_calc_time = end2-start2;
  printf(" call calc time: %u\n", (unsigned) call_calc_time);
  printf("  put calc time: %u\n", (unsigned) put_calc_time);

  printf("%llu\n", ts2());

  return 0;

}

