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
	double sqrt_t = sqrt(t);
	double rt = r*t;
	double vsqrt_t = v*sqrt_t;
	double d1 = (log(s/k)+rt)/vsqrt_t;
	double d2 = d1 - vsqrt_t;
	double dt = d*t;
	double exp_dt = exp(-dt);
	double exp_rt = exp(-rt);
	double price = 0;
	swith(cp_flag) {
		case 'c': 
			price = s*exp_dt*gsl_cdf_ugaussian_P( d1 ) - k*exp_rt*gsl_cdf_ugaussian_P(d2);
			break;
		case 'p': 
			price = k*exp_rt*gsl_cdf_ugaussian_P( -d2 ) - s*exp_dt*gsl_cdf_ugaussian_P(-d1);
			break;
		default:
			printf("Unacceptable option type.\nPlease specify 'c' or 'p'.\n");
	}
	return price;
}


int
main (void)
{
  double underlier_price = 87.5;
  double s = underlier_price;

  double strike_price = 85;
  double k = strike_price;

  double risk_free_rate = 0.005;
  double r = risk_free_rate;

  double time_to_maturity = 0.04;
  double t = time_to_maturity;

  double underlier_volatility = 0.06;
  double v = underlier_volatility;

  double discount_rate = 0;
  double d = discount_rate;

  printf("Underlier price: %f\n", s);
  printf("   Strike price: %f\n", k);
  printf(" risk free rate: %0.05f\n", r);
  printf(" Time to expiry: %0.05f\n", t);
  printf("     Volatility: %0.05f\n", v);
  printf("  Discount rate: %0.05f\n", d);
  
  printf("\n");
  printf("price call: %f\n", price('c', s,k,r,v,t,d));
  printf("price  put: %f\n", price('p', s,k,r,v,t,d));
  
  return 0;
}

