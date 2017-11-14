						/*******************************/
						/*          MemAlloc.c         */
						/*******************************/


#include "all.h"

extern void GridsMemFree()
{
	int SizeFr;

	/* Deallocate memory for input matrices													*/ 
	iMemFree2d(ishp,m,n);
	iMemFree2d(isoil,m,n);
	iMemFree2d(iman,m,n);
	fMemFree2d(e,m,n);
	fMemFree2d(ret,m,n);

	if(chancheck == 1)
	{
		iMemFree2d(link,m,n);
		iMemFree2d(node,m,n);
	}

	fMemFree2d(sdep,m,n);

	/* Deallocate memory for output matrices												*/ 
	
	if(indexinf == 1)	fMemFree2d(vinf,m,n);

	fMemFree2d(h,m,n);
	fMemFree2d(hch,m,n);

	if(indexeros == 1)
	{
		fMemFree2d(qss,m,n);
		fMemFree2d(MaxFluxCout,m,n);
		fMemFree2d(totsus,m,n);
		fMemFree2d(SusC,m,n);
		fMemFree2d(totnetv,m,n);

		/* Deallocate memory for 3-D matrices													*/ 
		for (SizeFr=0;SizeFr<4;SizeFr++)
		{
			fMemFree2d(qovs[SizeFr],m,n);
			fMemFree2d(vols[SizeFr],m,n);
			fMemFree2d(ssoil[SizeFr],m,n);
			fMemFree2d(SedFluxOut[SizeFr],m,n);
			fMemFree2d(MFAC[SizeFr],m,n);
		}
	}

	fMemFree2d(dqov,m,n);
	fMemFree2d(dqch,m,n);
	fMemFree2d(rtot,m,n);
	fMemFree2d(wrint,m,n);
}


			/**********************************/ 
			/*        FCT:  fMemFree2d         */ 
			/**********************************/ 

/* Deallocates memory for a floating 2D-grid of NoRows*NoCols			*/		
void fMemFree2d(float** matrix2d, int NoRows, int NoCols)
{
	int k;

	for(k=0; k<(NoRows+1); k++)
	{
		free(*(matrix2d + k));
	}

	free(matrix2d);
} 

/* Deallocates memory for a integer 2D-grid of NoRows*NoCols			*/		
void iMemFree2d(int** matrix2d, int NoRows, int NoCols)
{
	int k;

	for(k=0; k<(NoRows+1); k++)
	{
		free(*(matrix2d + k));
	}

	free(matrix2d);
} 