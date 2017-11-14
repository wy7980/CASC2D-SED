						/*******************************/
						/*          Settling.c         */
						/*******************************/

/* At each time step and by size fraction, calculates the volume  */
/* of sediment in suspension that deposits.  This volume is sub-  */
/* tracted from the suspended portion and added to the deposited  */
/* portion                                                        */

#include "all.h"

extern void Settling()
{
	int j,k,SizeFr;
	float depth, settlPerc[4], settl[4];

	for(j=1;j<=m;j++)
	{
	 for(k=1;k<=n;k++)
	 {
		 if(ishp[j][k] != nodatavalue)
		 {
			 if (ishp[j][k] == 1) depth = h[j][k];
			 if (ishp[j][k] == 2) depth = hch[j][k];

			 if(depth > 0)
			 {
					for (SizeFr=1;SizeFr<=3;SizeFr++)
					{
						/* Settling is calculated for													*/
						/* SizeFr=1 (sand); 2 (silt) and 3 (clay)							*/

						if(depth > ws[SizeFr]*dt)
						{
							settlPerc[SizeFr] = (float)(ws[SizeFr] * dt / depth);
						}
						else
						{
							settlPerc[SizeFr] = 1;
						}

						settl[SizeFr] = qovs[SizeFr][j][k] * settlPerc[SizeFr];
						vols[SizeFr][j][k] += settl[SizeFr];
						qovs[SizeFr][j][k] -= settl[SizeFr];
					}
			 }
		 }
		}
	}

}