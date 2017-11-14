						/*******************************/
						/*          SedStats.c         */
						/*******************************/


#include "all.h"

extern void SedStats()
{
	int j,k, SizeFr;
	float totdepv,totscourv;

	for(j = 1;j <= m; j++)
	{
		for(k = 1;k <= n; k++)
		{
			if(ishp[j][k] != nodatavalue)
			{
				totdepv = 0.0;
				totscourv = 0.0;
				totsus[j][k] = 0.0;

				for(SizeFr=1;SizeFr<=3;SizeFr++)
				{
					/* Total (sand+silt+clay) deposited sed. volume (m3)		*/

					totdepv += vols[SizeFr][j][k];

					/* Total (sand+silt+clay) scoured sed. volume (m3)  		*/

					totscourv += ssoil[SizeFr][j][k];

					/* Total (sand+silt+clay) suspended sed. volume (m3)		*/

					totsus[j][k] += qovs[SizeFr][j][k];
				}

				/* Net (deposited - eroded) sediment volume (mm)					*/

				totnetv[j][k] = (totdepv + totscourv) * 1000 / (w*w);

				/* Min. and Max. net erosion/depostion volume (m3)				*/

				aminnetv = MIN((double)(totnetv[j][k]) , aminnetv);
				amaxnetv = MAX(totnetv[j][k] , amaxnetv);

				/* Absolute max. flux conc., susp. volume and suspended		*/
				/* conc. at any time step and at any overland cell				*/

				if(ishp[j][k] == 1)
				{
					amaxFluxCoutOv = MAX(MaxFluxCout[j][k],amaxFluxCoutOv);
					amaxSusOv = MAX(totsus[j][k],amaxSusOv);

					/* Limiting the mim. water depth to 0.5mm will reduce		*/
					/* very high concentration calculations									*/
					if(h[j][k] > 5E-4)
					{
						SusC[j][k] = totsus[j][k] / (h[j][k]*w*w);
						amaxSusCov = MAX(amaxSusCov,SusC[j][k]);
					}
					else
					{
						SusC[j][k] = 0;
					}
				}

				/* Absolute max. flux conc., susp. volume and suspended		*/
				/* conc. at any time step and at any channel  cell				*/

				if(ishp[j][k] == 2)
				{

					amaxFluxCoutCh = MAX(amaxFluxCoutCh,MaxFluxCout[j][k]);
					amaxSusCh = MAX(amaxSusCh,totsus[j][k]);

					if(hch[j][k] > 5E-4)
					{
						SusC[j][k] = totsus[j][k] /
										 (hch[j][k]*w*chp[link[j][k]][node[j][k]][2]);

						amaxSusCch = MAX(amaxSusCch,SusC[j][k]);
					}
					else
					{
						SusC[j][k] = 0;
					}
				}
			}
		}
	}
}