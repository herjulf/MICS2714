#include <stdio.h>
#include <math.h>
/* 2017-04-27 -ro */

main()
{
  double a, m, no2, rsr0;
  
  m = 0.9986;
  a = 0.163;


  for(rsr0=0.1; rsr0 <= 15; rsr0 = rsr0*1.2)  { 
    no2 = a * pow(rsr0, m);
    printf(" RS/R0=%4.2f NO2=%4.2f ppm\n", rsr0, no2);
  }

}
