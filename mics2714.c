#include <stdio.h>
#include <math.h>
/* 2017-04-27 -ro */

#define MIC2714_M  0.9986
#define MIC2714_A  0.163
double m = MIC2714_M;
double a = MIC2714_A;

/*
  EC  20C 1013mB  NO2 1 ppb= 1.9125 μg/m**3 
  WHO 25C 1013mB  NO2 1 ppb= 1.88   μg/m**3 

  https://uk-air.defra.gov.uk/assets/documents/reports/cat06/0502160851_Conversion_Factors_Between_ppb_and.pdf

*/

#define NO2_CONV_EC  1.9125
#define NO2_CONV_WHO 1.88

double mics2714(double vcc, double v0, double corr)
{
  double no2, rsr0;
  /* Voltage divider */
  rsr0 = (vcc - v0)/v0;
  /* Transfer function */
  no2 = a * pow(rsr0, m);
  return no2 + corr;
}

main()
{
  double v0, no2, rsr0, vcc = 5;

  for(v0 = 0.02; v0 <= 4.6; v0 += 0.1)  { 
    no2 = mics2714(vcc, v0, 0);
    rsr0 = (vcc-v0)/v0;
    printf(" v0=%4.2f rsr0=%4.2f NO2=%4.2f ppm\n", v0, rsr0, no2);
  }
  v0 = 2.5;
  no2 = mics2714(vcc, v0, 0);
  rsr0 = (vcc-v0)/v0;
  printf("Half v0=%4.2f rsr0=%4.2f NO2=%4.2f ppm\n", v0, rsr0, no2);
}

void print_function(void)
{  
  double no2, rsr0;
  
  for(rsr0=0.1; rsr0 <= 15; rsr0 = rsr0*1.2)  { 
    no2 = a * pow(rsr0, m);
    printf(" RS/R0=%4.2f NO2=%4.2f ppm\n", rsr0, no2);
  }
}
