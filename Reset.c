						/*******************************/
						/*            Reset.c          */
						/*******************************/

/* For each time step and cell resets the following variables to  */
/* zero:                                                          */
/*		MaxFluxCout: maximum flux-averare concentration             */
/*		MFAC: maximum flux-average concentration by size fraction   */
/*		qss: Total volume of sediment out of each cell              */
/*		SedFluxOut: Total volume of sediment out of each cell by    */
/*                size fraction                                   */

#include "all.h"

extern void Reset()
{
	int j,k,SizeFr;

	for(j=1; j<=m; j++)
	{
		for(k=1; k<=n; k++)
		{
			MaxFluxCout[j][k] = 0.0;
			qss[j][k] = 0.0;

			for (SizeFr=1;SizeFr<=3;SizeFr++)
			{
				SedFluxOut[SizeFr][j][k] = 0.0;
				MFAC[SizeFr][j][k] = 0.0;
			}
		}
	}
}