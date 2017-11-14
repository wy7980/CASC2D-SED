

						/*******************************/ 
						/*         Fcts_stats.c        */ 
						/*******************************/ 


#include "all.h"


			/**********************************/ 
			/*           FUNCT: gridstats     */ 
			/**********************************/ 


/* Determines the mean and standard deviation of a grid						*/ 	

extern struct gstats gridstats(float **inputgrid)

{
	struct gstats statistics;
	float s;
	int j,k;

	statistics.min = 10E300;
	statistics.max = -10E300;
	statistics.mean = 0;
	s = 0;

	for(j=1;j<=m;j++)
	{
		for(k=1;k<=n;k++)
		{
			if(ishp[j][k] != nodatavalue)
			{
				statistics.min = MIN(statistics.min,inputgrid[j][k]);
				statistics.max = MAX(statistics.max,inputgrid[j][k]);
				statistics.mean += inputgrid[j][k] / ncells;
			}
		}
	}
	for(j=1;j<=m;j++)
	{
		for(k=1;k<=n;k++)
		{
			if(ishp[j][k] != nodatavalue)
			{
				s += 
				(float)(pow(inputgrid[j][k]-statistics.mean,2)/(ncells-1));
			}
		}
	}

	statistics.stdev = (float)(sqrt(s));

	return(statistics);
}



