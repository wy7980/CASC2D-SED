						/*******************************/
						/*         SedVolumes.c        */
						/*******************************/

/* Calculates at the end of the simulation the volume of          */
/* suspended, deposited and (suspended+deposited) sediment        */
/* by size fraction remaining in the overland or the channels     */
#include "all.h"

extern void	SedVolumes()
{
	int j,k,SizeFr;

	for(j=1;j<=m;j++)
	{
		for(k=1;k<=n;k++)
		{
			if(ishp[j][k] != nodatavalue)
			{
				/* Total eroded sediment by size fraction                 */
				for(SizeFr =1;SizeFr<=3;SizeFr++)
				 tot_eroded[SizeFr] += ssoil[SizeFr][j][k];

				if(ishp[j][k] == 1)  /* for the overland cells            */
				{
					for(SizeFr =1;SizeFr<=3;SizeFr++)
					{
						/* Total suspended volume by size fraction            */
						sus_ov[SizeFr] += qovs[SizeFr][j][k];

						/* Total deposited volume by size fraction            */
						dep_ov[SizeFr] += vols[SizeFr][j][k];

						/* Total suspended and deposited volume by size fract.*/
						tot_ov[SizeFr] += qovs[SizeFr][j][k] +
															vols[SizeFr][j][k];
					}
				}

				if(ishp[j][k] == 2)  /* for the channel cells             */
				{
					for(SizeFr =1;SizeFr<=3;SizeFr++)
					{
						/* Total suspended volume by size fraction            */
						sus_ch[SizeFr] += qovs[SizeFr][j][k];

						/* Total deposited volume by size fraction            */
						dep_ch[SizeFr] += vols[SizeFr][j][k];

						/* Total suspended and deposited volume by size fract.*/
						tot_ch[SizeFr] += qovs[SizeFr][j][k] +
															vols[SizeFr][j][k];
					}
				}
			}
		}
	}
}