						/*******************************/ 
						/*         OvrlDepth.c         */ 
						/*******************************/ 


#include "all.h"


extern void OvrlDepth( )
{

	int j,k,l,rindex,icall;
	float hov;

	/*******************************/ 
	/*    Read rainfall intensity  */ 
	/*******************************/ 

	icall = 0;
	rindex = 1;

	if(iter > nitrn) rindex = 0;
	if(iter <= nitrn && irain == 1)
	{
		icall=1;

		raincount = raincount + 1;

		if(raincount == nread+1) raincount = 1;

		if(raincount == 1)
		{
			for(l=1;l<=nrg;l++)
			{
				fscanf(rain_file_fptr,"%f ",&rrg[l]);
			}
		}
	}

	/**********************************************/ 
	/*    Updating overland depth (water balance) */ 
	/**********************************************/ 

	/* Applying the Rainfall to each Grid Cell within the Watershed */ 

	for(j=1;j<=m;j++)
	{
		for(k=1;k<=n;k++)
		{
			if(ishp[j][k] != nodatavalue)
			{
				if(irain == 0)  /* Uniform Rainfall */ 
				{
					/* Convert uniform rainfall intensity: mm/h -> m/s			*/
					
					wrint[j][k] = (float)(crain/3600.0/1000.0);

					/* Rainfall rate reduced until intercept. is satisfied	*/

					if (ret[j][k] != 0)	intercept(j,k);
				}
				else      /* Spatially Distributed Rainfall */  
				{
					if(icall == 1)
					{
						rain(j,k);
					}
				}

				if(iter > nitrn) wrint[j][k] = 0.0;

				/* Determining the Min. and Max. Rainfall Intensity				*/
				
				if(wrint[j][k] <= aminrain) aminrain=wrint[j][k];
				if(wrint[j][k] >= amaxrain) amaxrain=wrint[j][k];

				/* Determines total rainfall depth */ 

				rtot[j][k] = rtot[j][k] + wrint[j][k]*dt;

				/* Computing the Overland Depth due to the Overland Flow	*/

				hov = dqov[j][k] * dt / (w*w); 

				/* Computing the Total Overland Depth due to the					*/ 
				/* overland flow, previous overland depth, plus rainfall	*/ 
				/* minus 	interception   																	*/ 
				
				hov = hov + h[j][k] + rindex * wrint[j][k] * dt;

				h[j][k] = hov;

				/* When HOV < 0, then a negative depth situation occurs. */ 
				
				if(hov < 0.0)
				{
					if(hov > -0.0001) hov = 0;
					else
					{
						
						fprintf(Summ_file_fptr,
							"Negative Depth (HOV = %f) in the Overland Plane \n",
																															hov);
						fprintf(Summ_file_fptr,
							      "Grid Cell : Row = %ld   Column = %ld \n",j,k);
						fprintf(Summ_file_fptr,
							               "dqov[%ld][%ld] * dt / (w*w) = %f \n",
																					j,k,dqov[j][k]*dt/(w*w));
						fprintf(Summ_file_fptr,"rint[%ld][%ld] = %f \n",
																									 j,k,wrint[j][k]);
						fprintf(Summ_file_fptr,"h[%ld][%ld] = %f \n",
																											j,k,h[j][k]);
						RunTime(clock());

						GridsMemFree();

						exit(0);
					}
				}

				/* Calling the Infiltration Subroutine. HOV will be				*/ 
				/* modified by subtracting	the infiltration losses.			*/ 
				/* NOTE : If the infiltration volume that can be	lost		*/ 
				/* for DT is greater than the amount of surface 					*/ 
				/* volume present, then HOV will be reduced to zero.			*/ 

				if(indexinf == 1) infilt(j,k);					

				/* Determining the Minimum and Maximum Overland Depth 		*/ 
				/* and	the Minimum and Maximum Infiltration Depth				*/ 

				if(h[j][k] < amindepth) amindepth = h[j][k];
				if(h[j][k] > amaxdepth) amaxdepth = h[j][k];

				if(vinf[j][k] < aminvinf) aminvinf = vinf[j][k];
				if(vinf[j][k] > amaxvinf) amaxvinf = vinf[j][k];

				/* Once used in the water balance calculation, this				*/ 
				/* variable	is reset to zero. It will be recalculated			*/ 
				/* in the next time step in the ov. flow routing					*/ 
				
				dqov[j][k] = 0.0;  
													 
				if(iter == niter)  /* Last computation step */ 
				{
					/* Total Volume of Rainfall minus interception;					*/ 
					
					vin = vin + rtot[j][k] * w * w;
					
					/* Total Volume of Infiltration													*/ 
					
					vinftot = vinftot + vinf[j][k] * w * w; 
				}
			}
		}
	}
}