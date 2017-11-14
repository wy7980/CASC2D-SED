						/*******************************/ 
						/*       InitializeVars.c      */ 
						/*******************************/ 


#include "all.h"

extern void InitializeVars()
{
	int SizeFr,i,j,k;
	
	/* Grid values																									*/ 
	for(j=1;j<=m;j++)
	{
		for(k=1;k<=n;k++)
		{	
			if(ishp[j][k] != nodatavalue)
			{
				/* retention depth was entered in mm.												*/ 
				ret[j][k] = retention[iman[j][k]] / 1000; 
				dqov[j][k] = 0.0;
				dqch[j][k] = 0.0;
				vinf[j][k] = 0.0;
				rtot[j][k] = 0.0;
				MaxFluxCout[j][k] = 0.0;
				qss[j][k] = 0.0;
				wrint[j][k] = 0.0;

				for (SizeFr=1;SizeFr<=3;SizeFr++)
				{
					vols[SizeFr][j][k] = 0.0;
					ssoil[SizeFr][j][k] = 0.0;
					qovs[SizeFr][j][k] = 0.0;
					SedFluxOut[SizeFr][j][k] = 0.0;
					MFAC[SizeFr][j][k] = 0.0;
				}
			}
		}
	}

	/* Total volumes																								*/ 
	vin = 0.0;
	vout = 0.0;
	vinftot = 0.0;

	/* Counters																											*/ 
	raincount = 0;
	icount = 1;
  ipcount = 1;
  ifcount = 1;

	/* Variables that hold min. and max. values											*/ 
	amaxdepth = 9e-30;
	amindepth = 9e30;
	amaxcdepth = 9e-30;
	amincdepth = 9e30;
	amaxvinf = 9e-30;
	aminvinf = 9e30;
	amaxnetv = 9e-30;
	aminnetv = 9e30;
	amaxFluxCoutOv = 9e-30;
	amaxFluxCoutCh = 9e-30;
	amaxrain = 9e-30;
	aminrain = 9e30;
	amaxSusOv = 9e-30;
	amaxSusCh = 9e-30;
	amaxSusCov = 9e-30;
	amaxSusCch = 9e-30;

	/* Sediment volumes by size fraction (sand/silt/clay)						*/ 
	for (SizeFr=1;SizeFr<=3;SizeFr++)
	{
		tot_eroded[SizeFr] = 0.0;	/* Eroded	during the simulation			*/ 
		sus_ov[SizeFr] = 0.0;		/* Suspended remaining on overl.			*/  
		dep_ov[SizeFr] = 0.0;		/* Deposited remaining on overl.			*/ 
		tot_ov[SizeFr] = 0.0;		/* Susp.+ Dep. remaining on overl.		*/ 
		sus_ch[SizeFr] = 0.0;		/* Suspended remaining in channels		*/ 
		dep_ch[SizeFr] = 0.0;		/* Deposited remaining in channels		*/ 
		tot_ch[SizeFr] = 0.0;		/* Susp.+ Dep. remaining in channels	*/ 
		sed_out[SizeFr] = 0.0;
	}

	/* Water volumes at the beggining & end of the  simulation			*/ 
	init_ov_vol = 0.0;
	init_ch_vol = 0.0;
	final_ov_vol = 0.0;
	final_ch_vol = 0.0;

	/* Sediment characts. for medium grain sizes at 20 degrees C		*/ 
	ds[1] = 0.00035;					/* Sand median diameter [m]		0.00035	*/ 
	ds[2] = 0.000016 ;				/* Silt median diameter [m]		0.000016*/ 
	ds[3] = 0.000001;					/* Clay median diameter [m]		0.000001*/ 
	ws[1] = 0.036;						/* Sand fall veleocity (m/s)	0.036		*/ 
	ws[2] = 2.2e-4;						/* Silt fall velocity	(m/s)		2.2e-4	*/ 
	ws[3] = 8.6e-7;						/* Clay fall velocity	(m/s)		8.6e-7	*/ 

	/* Initializing ICHN Array.  NOTE: it is assumed that the max.	*/ 
	/* number of nodes at any link is 100														*/ 
	for(i=1;i<=maxlink;i++)
		for(k=1;k<=2;k++)
			for(j=1;j<=99;j++)
				ichn[i][j][k] = 0;

	/* Initializing channel and overland water depths								*/ 
	for(j=1;j<=m;j++)
	{
		for(k=1;k<=n;k++)
		{
			hch[j][k] = 0.0;

			if(indexsdep == 1)
			{
				h[j][k] = sdep[j][k];

				if(sdep[j][k] > 0.0 && chancheck == 1 && link[j][k] > 0)
				{
					hch[j][k] = sdep[j][k];

					if(sdep[j][k] > chp[link[j][k]][node[j][k]][3])
					{
						h[j][k] = sdep[j][k] - chp[link[j][k]][node[j][k]][3];
					}
					else
					{
						h[j][k] = 0.0;
					}
				}		
			}
			else
			{
				h[j][k] = 0.0;
				sdep[j][k] = 0.0;
			}
		}
	}
}