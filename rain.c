						/*******************************/ 
						/*             rain.c          */ 
						/*******************************/ 


#include "all.h"

extern void rain(int j,int k)
{
	float totdist = 0.0;
	float totrain = 0.0;

	float xc,yc,dist,xul,yul;
	int l;
    
	wrint[j][k] = -999.0;

	xul = xllcorner;
	yul = yllcorner + m * w; 

	if(nrg == 1)
	{
		wrint[j][k] = rrg[1];
	}
	else
	{
		for(l=1;l<=nrg;l++)
		{
			yc = (float)(yul - j * w + w / 2.0);
			xc = (float)(xul + k * w - w / 2.0);

			dist = (float)(sqrt(pow((yc-yrg[l]),2.0) + 
																					pow((xc-xrg[l]),2.0)));
			if(dist < 1e-5)
			{
				wrint[j][k] = rrg[l];
			}
			else
			{
				totdist = (float)(totdist + 1.0/pow(dist,2.0));
				totrain = (float)(totrain + rrg[l]/pow(dist,2.0));
			}
		}
	}

	if(wrint[j][k] == -999.0)
	{
		wrint[j][k] = totrain / totdist;
	}

  /* Changing Units from inches/hour to meters/second */ 

	wrint[j][k] = (float)(wrint[j][k] * 0.0254 / 3600.);
	
	/* Rainfall rate is reduced until interception is satisfied */ 

	if (ret[j][k] != 0)
	{
		intercept(j,k);
	}

}
