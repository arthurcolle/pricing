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
	if (cp_flag == 'c')
		return s*exp(-d*t)*gsl_cdf_ugaussian_P(d1)-k*exp(-r*t)*gsl_cdf_ugaussian_P(d2);
	
	if (cp_flag == 'p')
		return k*exp(-r*t)*gsl_cdf_ugaussian_P(-d2)-s*exp(-d*t)*gsl_cdf_ugaussian_P(-d1);
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
  
  printf("price c: %f\n", price('c', s,k,r,v,t,d));
  printf("price p: %f\n", price('p', s,k,r,v,t,d));
  
  return 0;
}

