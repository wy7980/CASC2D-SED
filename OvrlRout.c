						/*******************************/ 
						/*           OvrlRout.c        */ 
						/*******************************/ 

			/**********************************/ 
			/*        FUNCT: OvrlRout         */ 
			/**********************************/ 

#include "all.h"

extern void OvrlRout()
{

	int j,k,jj,kk,l;

	for(j=1;j<=m;j++)
	{
	 for(k=1;k<=n;k++)
	 {
		 if(ishp[j][k] != nodatavalue)
		 {
			 for(l=-1;l<=0;l++)
			 {
				 jj=j+l+1;
				 kk=k-l;

				 if(jj <= m && kk <=n && ishp[jj][kk] != nodatavalue)
				 {	   
					 ovrl(j,k,jj,kk);
				 }
			 }
		 }
	 }
	}
}

			/**********************************/ 
			/*         FUNCT: Ovrl            */ 
			/**********************************/ 

extern void ovrl( int j,int k, int jj, int kk)
{
	int jfrom,kfrom,jto,kto;

	float a=1.0;

	float vel = 0.0;

	float so,sf,dhdx,hh,rman,alfa,dqq,stordepth;
	
	so = (e[j][k] - e[jj][kk])/w;

	dhdx = (h[jj][kk] - h[j][k])/w;

	sf = so - dhdx +(float)(1e-30);

	hh = h[j][k];

	rman = pman[iman[j][k]];

	if(chancheck == 1 && link[j][k] > 0)
	{
		if(sdep[j][k] > chp[link[j][k]][node[j][k]][3]) 
		{
			stordepth = sdep[j][k] - chp[link[j][k]][node[j][k]][3];
		}
		else
		{
			stordepth = 0.0;
		}
	}
	else
	{
		stordepth = sdep[j][k];
	}

	if(sf < 0) 
	{
			hh = h[jj][kk];
			rman = pman[iman[jj][kk]];

			if(chancheck == 1 && link[jj][kk] > 0)
			{
				if(sdep[jj][kk] > chp[link[jj][kk]][node[jj][kk]][3]) 
				{
					stordepth = 
						sdep[jj][kk] - chp[link[jj][kk]][node[jj][kk]][3];
				}
				else
				{
					stordepth = 0.0;
				}
			}
			else
			{
				stordepth = sdep[jj][kk]; 
			}
	}

	if(hh >= stordepth)
	{
		alfa = (float)((pow(fabs(sf),0.5))/rman);

		/*	Note : The variable "a" represents the sign of the				*/ 
		/*	Friction Slope (Sf)	Computing Overland Flow								*/	

		if(sf >= 0) a = 1.0;

		if(sf < 0) a = -1.0;

		dqq = (float)(a*w*alfa*pow((hh-stordepth),1.667));

		dqov[j][k] = dqov[j][k] - dqq;

		dqov[jj][kk] = dqov[jj][kk] + dqq;
 
		/* Compute overland sediment flow and erosion/deposition			*/ 																																			
		
		if(indexeros == 1 && dqq != 0.0)
		{
			if(a > 0)        /* (J,K) to (JJ,KK) */
			{
				jfrom = j;
				kfrom = k;
				jto = jj;
				kto = kk;
			}
			else               /* (JJ,KK) to (J,K) */
			{
				jfrom = jj;
				kfrom = kk;
				jto = j;
				kto = k;
			}

			if (ishp[jfrom][kfrom] == 1)
			{
				RoutSedOvrl(dqq,sf,jfrom,kfrom,jto,kto);
			}
		}
	
	}	/* End of HH >= STORDEPTH */		

}   /* End of OVRL */ 