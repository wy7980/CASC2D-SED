						/*******************************/
						/*          MemAlloc.c         */
						/*******************************/


#include "all.h"

extern void GridsMemAlloc()
{
	int SizeFr;

	printf("starting memmory allocation");
	/* Allocate memory for input matrices														*/ 
	ishp = intMemAlloc2d(m,n);
	isoil = intMemAlloc2d(m,n);
	iman  = intMemAlloc2d(m,n);
	e = floatMemAlloc2d(m,n);
	ret = floatMemAlloc2d(m,n);

	if(chancheck == 1)
	{
		link = intMemAlloc2d(m,n);
		node = intMemAlloc2d(m,n);
	}

	sdep = floatMemAlloc2d(m,n);
	
	/* Allocate memory for output matrices													*/ 
	
	if(indexinf == 1)	vinf = floatMemAlloc2d(m,n);

	h = floatMemAlloc2d(m,n);
	hch = floatMemAlloc2d(m,n);

	if(indexeros == 1)
	{
		qss = floatMemAlloc2d(m,n);
		MaxFluxCout = floatMemAlloc2d(m,n);
		totsus = floatMemAlloc2d(m,n);
		SusC = floatMemAlloc2d(m,n);
		totnetv = floatMemAlloc2d(m,n);

		/* Allocate memory for 3-D matrices														*/ 
		for (SizeFr=0;SizeFr<4;SizeFr++)
		{
			qovs[SizeFr] = floatMemAlloc2d(m,n);
			vols[SizeFr] = floatMemAlloc2d(m,n);
			ssoil[SizeFr] = floatMemAlloc2d(m,n);
			SedFluxOut[SizeFr] = floatMemAlloc2d(m,n);
			MFAC[SizeFr] = floatMemAlloc2d(m,n);
		}
	}

	dqov = floatMemAlloc2d(m,n);
	dqch = floatMemAlloc2d(m,n);
	rtot = floatMemAlloc2d(m,n);
	wrint = floatMemAlloc2d(m,n);

	printf("memory allocation ends");
}
			/**********************************/ 
			/*         intMemAlloc2d          */ 
			/**********************************/ 

/* Allocates memory for a integer 2D-grid of NoRows*NoCols */ 
int** intMemAlloc2d(int NoRows, int NoCols)
{
	int k;
	int** matrix2d;

	matrix2d = (int **)malloc((NoRows+1)*sizeof(int *));

	for(k=0; k<(NoRows+1); k++)
	{
		*(matrix2d + k) =(int*)malloc((NoCols+1)*sizeof(int));
	}

	return matrix2d;
}

			/**********************************/ 
			/*        floatMemAlloc2d         */ 
			/**********************************/ 

/* Allocates memory for a floating 2D-grid of NoRows*NoCols */ 
float** floatMemAlloc2d(int NoRows, int NoCols)
{
	int k;
	float** matrix2d;

	matrix2d = (float **)malloc((NoRows+1)*sizeof(float *));

	for(k=0; k<(NoRows+1); k++)
	{
		*(matrix2d + k) =(float*)malloc((NoCols+1)*sizeof(float));
	}

	return matrix2d;
}