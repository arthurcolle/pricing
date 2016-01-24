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
	double d1 = (log(s/k)+r*t)/(v*sqrt_t);
	double d2 = d1-(v*sqrt_t);
	double exp_dt = exp(-d*t);
	double exp_rt = exp(-r*t);
	double price = 0;

	if (cp_flag == 'c')
		price = s*exp_dt*gsl_cdf_ugaussian_P(d1)-k*exp_rt*gsl_cdf_ugaussian_P(d2);
	if (cp_flag == 'p')
		price = k*exp_rt*gsl_cdf_ugaussian_P(-d2)-s*exp_dt*gsl_cdf_ugaussian_P(-d1);
	return price;
}


int
main (void)
{
  double s = 87.5;
  double k = 85;
  double r = 0.005;
  double t = 0.04;
  double v = 0.06;
  double d = 0;
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

