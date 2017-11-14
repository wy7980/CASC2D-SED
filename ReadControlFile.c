						/*******************************/ 
						/*      ReadControlFile.c      */ 
						/*******************************/ 


#include "all.h"


extern void ReadControlFile()
{
	int i,j,l;

	printf("Reading CONTROL file \n");

	fprintf(Summ_file_fptr,"\nCONTROL Input Data \n");
	fprintf(Summ_file_fptr,	 "================== \n");
	fprintf(Summ_file_fptr,	 "Control file : %s\n", control_file);

	fscanf(control_file_fptr,"%f %ld %ld %ld %ld",
				&dt,&niter,&nitrn,&nprn,&nplt);

	fprintf(Summ_file_fptr,
	"DT = %2.2f sec NITER= %ld NITRN = %ld NPRN = %ld NPLT = %ld\n\n",
															dt,niter,nitrn,nprn,nplt);

	fprintf(Summ_file_fptr,"Overland outlet cell: \n");
	fscanf(control_file_fptr,"%ld %ld %f",&jout,&kout,&sovout);
	fprintf(Summ_file_fptr,"JOUT = %ld KOUT = %ld SOVOUT = %g \n\n",
																								jout,kout,sovout);

	fscanf(control_file_fptr,"%i",&chancheck);
	fprintf(Summ_file_fptr,"CHANCHECK= %i \n",chancheck);

	fscanf(control_file_fptr,"%f",&elconv);
	fprintf(Summ_file_fptr,"ELCONV = %.2f\n",elconv);

	fprintf(Summ_file_fptr,"\nRainfall Data \n");
	fprintf(Summ_file_fptr,	 "============= \n");

	fscanf(control_file_fptr,"%ld ",&irain);
	fprintf(Summ_file_fptr,"IRAIN = %ld \n",irain);
	
	if(irain == 0)
	{
	 fscanf(control_file_fptr,"%f ",&crain);
	 fprintf(Summ_file_fptr,"CRAIN = %.3f (mm/h)\n",crain);
	}
	else
	{
	 fprintf(Summ_file_fptr,"Rainfall file: %s \n",rain_file);
	 fscanf(control_file_fptr,"%ld %ld ",&nrg,&nread);
	 fprintf(Summ_file_fptr,"NRG = %ld NREAD = %ld \n",nrg,nread);

	 xrg = (float*) malloc((nrg+1)*sizeof(float));
	 yrg = (float*) malloc((nrg+1)*sizeof(float));
	 rrg = (float*) malloc((nrg+1)*sizeof(float));
 
	 for(l=1;l<=nrg;l++)
	 {
		 fscanf(control_file_fptr,"%f %f ",&xrg[l],&yrg[l]);
		 fprintf(Summ_file_fptr,"XRG[%ld] = %8.6f\tYRG[%ld] = %8.6f \n",
																						l,xrg[l],l,yrg[l]);
	 }
	}

	fprintf(Summ_file_fptr,"\nLand Use Parameters \n");
	fprintf(Summ_file_fptr,	 "=================== \n");

	/* Allocate memory for the variables derived from the landuse		*/ 
	pman = (float*) malloc((nman+1)*sizeof(float));
	retention = (float*) malloc((nman+1)*sizeof(float));
	cfactor = (float*) malloc((nman+1)*sizeof(float));
	pfactor = (float*) malloc((nman+1)*sizeof(float));

	fscanf(control_file_fptr," %ld %ld ",&nman,&indexsdep);
	fprintf(Summ_file_fptr,"NMAN = %ld INDEXSDEP = %ld \n\n",
																							nman,indexsdep);
	fprintf(Summ_file_fptr,"\tIndex\tManning    Intercept.\tCusle\tPusle\n");
	fprintf(Summ_file_fptr,"\t-----\t-- n --    -- [mm] --\t-----\t-----\n");

	for(i=1;i<=nman;i++)
	{
	 fscanf(control_file_fptr,"%f %f %f %f",
					&pman[i], &retention[i],&cfactor[i],&pfactor[i]);
	 fprintf(Summ_file_fptr,
			"\t%3ld%11.3f\t%10.3f\t%5.3f\t%5.3f\n",
			               i,pman[i],retention[i],cfactor[i],pfactor[i]);
	}

	fprintf(Summ_file_fptr,"\nSoil type Parameters \n");
	fprintf(Summ_file_fptr,	 "==================== \n");
	
	fscanf(control_file_fptr,"%i %i %i",&indexinf,&indexeros,&nsoil);
	fprintf(Summ_file_fptr,"INDEXINF= %i INDEXEROS= %i NSOIL= %i \n",
																				indexinf,indexeros,nsoil);

	fprintf(Summ_file_fptr,
		"\n        Index    Ks       G         Md       %%Sand     %%Silt     %%Clay     Kusle\n");
	fprintf(Summ_file_fptr,	 
		"        -----  [cm/h]    [cm]      -----     -----     -----     -----     -----\n");
	if(indexinf == 1)
	{
	 pinf = floatMemAlloc2d(nsoil,8);

	 /* Read values from the CONTROL file */ 
	 for(i=1;i<=nsoil;i++)
	 {
		 fprintf(Summ_file_fptr,"%10i",i);
		 for(j=1;j<=7;j++)
		 {
			 fscanf(control_file_fptr,"%g ",&pinf[i][j]);
			 fprintf(Summ_file_fptr,"%10.3f",pinf[i][j]);
			 /* Converts Ks: cm/h -> m/s																*/ 
			 if(j ==1) pinf[i][j] = pinf[i][j]/3600/100; 
			 /* Converts G:  cm -> m																		*/ 
			 if(j ==2) pinf[i][j] = pinf[i][j]/100;      
		 }

		 fprintf(Summ_file_fptr,"\n");
	 }
	}

	fprintf(Summ_file_fptr,"\nInternal Gages Data \n");
	fprintf(Summ_file_fptr,	 "------------------- \n");

	fscanf(control_file_fptr,"%ld %ld %i",&indexdis,&ndis, &unitsQ);
	fprintf(Summ_file_fptr,
		                 "INDEXDIS = %ld  NDIS = %ld  Q_units = %i \n",
													                 indexdis,ndis, unitsQ);

	if(indexdis == 1)
	{
	  fprintf(Summ_file_fptr,"\n        Gage      Row      Column      Area\n");
		fprintf(Summ_file_fptr,"        ----      ---      ------     [has]\n");
		iq = intMemAlloc2d(ndis,2);
		areaQ = (float*) malloc((ndis+1)*sizeof(float));

		for (i=1;i<=ndis;i++)
		{
		 fprintf(Summ_file_fptr,"        %2i",i);
		 for (j=1;j<=2;j++)
		 {
			 fscanf(control_file_fptr,"%ld ",&iq[i][j]);
			 fprintf(Summ_file_fptr,"%10i",iq[i][j]);
		 }
		 fscanf(control_file_fptr,"%f", &areaQ[i]);
		 fprintf(Summ_file_fptr,"%14.3f\n", areaQ[i]);
		}
	}


	fprintf(Summ_file_fptr,"\nInternal Sediment Gages Data \n");
	fprintf(Summ_file_fptr,	 "---------------------------- \n");

	fscanf(control_file_fptr,"%ld %ld %i",&indexsed,&nsed, &unitsQs);
	fprintf(Summ_file_fptr,
										 "INDEXSED = %ld  NSED = %ld Qs_Units = %i\n",
																				  indexsed,nsed, unitsQs);

	if(indexsed == 1)
	{
		fprintf(Summ_file_fptr,"\n        Gage      Row      Column      Area\n");
		fprintf(Summ_file_fptr,"        ----      ---      ------     [has]\n");
		ised = intMemAlloc2d(nsed,2);
		areaQs = (float*) malloc((nsed+1)*sizeof(float));

		for(i=1;i<=nsed;i++)
		{
		 fprintf(Summ_file_fptr,"        %2i",i);
		 for (j=1;j<=2;j++)
		 {
			 fscanf(control_file_fptr,"%ld ",&ised[i][j]);
			 fprintf(Summ_file_fptr,"%10i",ised[i][j]);
		 }
		 fscanf(control_file_fptr,"%f", &areaQs[i]);
		 fprintf(Summ_file_fptr,"%14.3f\n",areaQs[i]);
		}
	}

	printf("Successfully Read All CONTROL Information \n");
	fclose(control_file_fptr);

	/* Allocate memory for the vector that holds the flow						*/ 
	/* dicharge and sediment discharge at each of those locations		*/ 
	q =  (float*) malloc((ndis+1)*sizeof(float));
	qsed = (float*) malloc((nsed+1)*sizeof(float));

}