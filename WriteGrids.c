
						/*******************************/ 
						/*          WriteGrids.c       */ 
						/*******************************/ 


#include "all.h"

extern void WriteGrids()
{		
	int j1,k1;

	float **WatDep;

	char wr_rname[80],wr_vinfname[80],wr_dname[80],
		wr_cname[80],wr_susname[80],wr_erosdepname[80],
		wr_sandfluxname[80],wr_siltfluxname[80],
		wr_clayfluxname[80],wr_totalfluxname[80],
		wr_sandMFACname[80],wr_siltMFACname[80],
		wr_clayMFACname[80],wr_totalMFACname[80];
			
	FILE *wr_dname_h = NULL;
	FILE *wr_erosdepname_h = NULL;
	FILE *wr_rname_h = NULL;
	FILE *wr_sandfluxname_h = NULL;
	FILE *wr_siltfluxname_h = NULL;
	FILE *wr_clayfluxname_h = NULL;
	FILE *wr_totalfluxname_h = NULL;
	FILE *wr_sandMFACname_h = NULL;
	FILE *wr_siltMFACname_h = NULL;
	FILE *wr_clayMFACname_h = NULL;
	FILE *wr_totalMFACname_h = NULL;
	FILE *wr_cname_h = NULL;
	FILE *wr_vinfname_h = NULL;
	FILE *wr_susname_h = NULL;

	WatDep = floatMemAlloc2d(m,n);
	

	if(ipcount == nplt)
  {
		printf("Writing Output Grids, IFCOUNT = %ld  Time = %.2f \n",
																							ifcount,iter*dt/60.);
				
		/* SusC: grid holds the values of total suspended sediment		*/ 
		/* WatDep: water depth in basin's overland or channel cells		*/ 
		
		for(j1=1; j1<=m; j1++)
		{
			for(k1=1; k1<=n; k1++)
			{		
				if (ishp[j1][k1] != nodatavalue)
				{
					if(ishp[j1][k1] == 1)
					{
						WatDep[j1][k1] = h[j1][k1];
					}
					else
					{
						WatDep[j1][k1] = hch[j1][k1];
					}
				}
			}
		}

		/* Writing time series grids																	*/ 

		/* Water depth in meters																			*/  
		write2dTS(dname, wr_dname,wr_dname_h,WatDep,1);

		/* Rainfall intensity in mm/h																	*/ 
		write2dTS(rname, wr_rname,wr_rname_h,wrint,3600000);

		/* Infiltrated volume in mm																		*/ 
		write2dTS(vinfname,wr_vinfname,wr_vinfname_h,vinf,1000);

		/* Suspended sediment concentration in m3/m3									*/ 
		write2dTS(cname,wr_cname,wr_cname_h,SusC,1);

		/* Total suspended sediment in mm															*/ 
		write2dTS(susname,wr_susname,wr_susname_h,totsus,1000/(w*w));

		/* Erosion and deposition in mm																*/ 
		write2dTS(erosdepname,wr_erosdepname,wr_erosdepname_h,
								totnetv,1);

		/* Sediment fluxes are in (m3/s)															*/ 
		write3dTS(sandfluxname,wr_sandfluxname,wr_sandfluxname_h,
								1, SedFluxOut);
		write3dTS(siltfluxname,wr_siltfluxname,wr_siltfluxname_h, 
								2, SedFluxOut);
		write3dTS(clayfluxname,wr_clayfluxname,wr_clayfluxname_h, 
								3, SedFluxOut);
		write2dTS(totalfluxname,wr_totalfluxname,wr_totalfluxname_h,
								qss,(1/dt));

		/* Sediment concentrations are in m3 sed/ m3 mixture					*/ 
		write3dTS(sandMFACname,wr_sandMFACname,wr_sandMFACname_h, 
								1, MFAC);
		write3dTS(siltMFACname,wr_siltMFACname,wr_siltMFACname_h, 
								2, MFAC);
		write3dTS(clayMFACname,wr_clayMFACname,wr_clayMFACname_h, 
								3, MFAC);
		write2dTS(totalMFACname,wr_totalMFACname,wr_totalMFACname_h,
								MaxFluxCout,1);

		/* Incrementing counters																			*/ 
		
		ifcount++;
		if (iter == 1) ipcount++;
		if (iter != 1) ipcount = 1;
   }
   else
   {
	   ipcount++;
   }

	 /* Freeing memory																							*/ 
	 
	 fMemFree2d(WatDep, m,n);
}


			/**********************************/ 
			/*         FUNCT: write2dTS       */ 
			/**********************************/ 

extern void write2dTS(char *name, char *wr_name,FILE *wr_name_h, 
								float **ParamValue, float UnitsConv)
{
	int j1,k1;

	if(name[0] != '\0') 
	{
		strncpy(wr_name,name,21);
		sprintf(wr_name,"%s.%ld",name,ifcount);
		if((wr_name_h=fopen(wr_name,"w"))==NULL)
		{
			printf("Can't open time-series file : %s \n",wr_name);
			exit(EXIT_FAILURE);
		}
		fprintf(wr_name_h,"%s",header);
				
		for(j1=1; j1<=m; j1++)
		{
			for(k1=1; k1<=n; k1++)
			{
				if (ishp[j1][k1] != nodatavalue)
				{
					fprintf(wr_name_h,"%10.5f ",ParamValue[j1][k1]*UnitsConv);
				}
				else
					fprintf(wr_name_h,"%i ",nodatavalue);
			}
			fprintf(wr_name_h,"\n"); 
		}

		fclose(wr_name_h);
	}
	return;

}


			/**********************************/ 
			/*         FUNCT: write3dTS       */ 
			/**********************************/ 

extern void write3dTS(char *name, char *wr_name,FILE *wr_name_h, 
								int layer, float **ParamValue[])
{
	int j1,k1;

	if(name[0] != '\0') 
	{
		strncpy(wr_name,name,21);
		sprintf(wr_name,"%s.%ld",name,ifcount);
		if((wr_name_h=fopen(wr_name,"w"))==NULL)
		{
			printf("Can't open time-series file : %s \n",wr_name);
			exit(EXIT_FAILURE);
		}
		fprintf(wr_name_h,"%s",header);
				
		for(j1=1; j1<=m; j1++)
		{
			for(k1=1; k1<=n; k1++)
			{
				if (ishp[j1][k1] != nodatavalue)
				{
					fprintf(wr_name_h,"%10.5f ",ParamValue[layer][j1][k1]);
				}
				else
					fprintf(wr_name_h,"%i ",nodatavalue);
			}
			fprintf(wr_name_h,"\n"); 
		}

		fclose(wr_name_h);
	}
	return;

}