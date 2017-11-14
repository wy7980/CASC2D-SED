						/*******************************/ 
						/*     ReadProjectFile.c       */ 
						/*******************************/ 


#include "all.h"

extern void ReadProjectFile(char ProjectName[80])
{

	char 	file_id[80];
	int ch;

	/* Initialize the output grid names to the null element					*/ 
	dname[0] = '\0';
	rname[0] = '\0';
	vinfname[0] = '\0';
	cname[0] = '\0';	
	susname[0] = '\0';
	erosdepname[0] = '\0';
	sandfluxname[0] = '\0';
	siltfluxname[0] = '\0';
	clayfluxname[0] = '\0';
	totalfluxname[0] = '\0';
	sandMFACname[0] = '\0';
	siltMFACname[0] = '\0';
	clayMFACname[0] = '\0';
	totalMFACname[0] = '\0';
	sed_out_file[0] = '\0';

	strncpy(project_file,ProjectName,80);

	printf("Project File           %s \n",project_file);
	
	if((project_file_fptr=fopen(project_file,"r"))==NULL)
	{printf("Can't open Project File : %s \n",project_file);
	 exit(EXIT_FAILURE);}

	/* Reading in the Data Filenames and Opening Files							*/ 

	printf("Starting to read the Project File \n");

	do{
			
	ch=fscanf(project_file_fptr,"%s",file_id); 

	if(ch!=EOF) 
	{	
		printf("FILE_ID = %s \n",&file_id);

		if(strcmp(file_id,"ELEVATION") == 0) 
		{
			ch=fscanf(project_file_fptr,"%s",elev_file);
			if((elev_file_fptr=fopen(elev_file,"r"))==NULL)
			{printf("Can't open Elevation File : %s \n",elev_file);
			 exit(EXIT_FAILURE);}
			printf("ELEVATION          %s \n",elev_file);
		}/*FRTP(file_id,"ELEVATION",elev_file_fptr,elev_file);*/ 
		if(strcmp(file_id,"PRECIP") == 0) 
		{
			ch=fscanf(project_file_fptr,"%s",rain_file);
			if((rain_file_fptr=fopen(rain_file,"r"))==NULL)
			{printf("Can't open Rain File : %s \n",rain_file);
			 exit(EXIT_FAILURE);}
			printf("PRECIP             %s \n",rain_file);
		}
		if(strcmp(file_id,"SOIL") == 0) 
		{
			ch=fscanf(project_file_fptr,"%s",soil_file);
			if((soil_file_fptr=fopen(soil_file,"r"))==NULL)
			{printf("Can't open Soil File : %s \n",soil_file);
			exit(EXIT_FAILURE);}
			printf("SOIL               %s \n",soil_file);
		}
		if(strcmp(file_id,"LANDUSE") == 0) 
		{
			ch=fscanf(project_file_fptr,"%s",iman_file);
			if((iman_file_fptr=fopen(iman_file,"r"))==NULL)
			{printf("Can't open Landuse File : %s \n",iman_file);
			exit(EXIT_FAILURE);}
			printf("LANDUSE            %s \n",iman_file);
		}
		if(strcmp(file_id,"CONTROL") == 0) 
		{
			ch=fscanf(project_file_fptr,"%s",control_file);
			if((control_file_fptr=fopen(control_file,"r"))==NULL)
			{printf("Can't open control File : %s \n",control_file);
			exit(EXIT_FAILURE);}
			printf("CONTROL              %s \n",control_file);
		}
		if(strcmp(file_id,"CHANNEL") == 0) 
		{
			ch=fscanf(project_file_fptr,"%s",chn_file);
			if((chn_file_fptr=fopen(chn_file,"r"))==NULL)
			{printf("Can't open Channel File : %s \n",chn_file);
			exit(EXIT_FAILURE);}
			printf("CHANNEL            %s \n",chn_file);
		}
		if(strcmp(file_id,"NODE") == 0) 
		{
			ch=fscanf(project_file_fptr,"%s",node_file);
			if((node_file_fptr=fopen(node_file,"r"))==NULL)
			{printf("Can't open Node File : %s \n",node_file);
			exit(EXIT_FAILURE);}
			printf("NODE            %s \n",node_file);
		}
		if(strcmp(file_id,"LINK") == 0) 
		{
			ch=fscanf(project_file_fptr,"%s",link_file);
			if((link_file_fptr=fopen(link_file,"r"))==NULL)
			{printf("Can't open Link File : %s \n",link_file);
			exit(EXIT_FAILURE);}
			printf("LINK            %s \n",link_file);
		}
		if(strcmp(file_id,"MASK") == 0) 
		{
			ch=fscanf(project_file_fptr,"%s",shap_file);
			if((shap_file_fptr=fopen(shap_file,"r"))==NULL)
			{printf("Can't open Shape File : %s \n",shap_file);
			exit(EXIT_FAILURE);}
			printf("MASK              %s \n",shap_file);
		}
		if(strcmp(file_id,"STORAGE_DEPTH") == 0) 
		{
			ch=fscanf(project_file_fptr,"%s",sdep_file);
			if((sdep_file_fptr=fopen(sdep_file,"r"))==NULL)
			{printf("Can't open Storage Depth File : %s \n",sdep_file);
			exit(EXIT_FAILURE);}
			printf("STORAGE_DEPTH              %s \n",sdep_file);
		}
		if(strcmp(file_id,"SUMMARY") == 0) 
		{
			ch=fscanf(project_file_fptr,"%s",Summ_file);
			if((Summ_file_fptr=fopen(Summ_file,"w"))==NULL)
			{printf("Can't open Output PRN File : %s \n",Summ_file);
			exit(EXIT_FAILURE);}
			printf("SUMMARY         %s \n",Summ_file);
		}
		if(strcmp(file_id,"DISCHARGE_OUT") == 0) 
		{
			ch=fscanf(project_file_fptr,"%s",dis_out_file);
			if((dis_out_file_fptr=fopen(dis_out_file,"w"))==NULL)
			{printf("Can't open Discharge File : %s \n",dis_out_file);
			exit(EXIT_FAILURE);}
			printf("DISCHARGE_OUT      %s \n",dis_out_file);
		}
		if(strcmp(file_id,"SEDIMENT_OUT") == 0) 
		{
			ch=fscanf(project_file_fptr,"%s",sed_out_file);
			if((sed_out_file_fptr=fopen(sed_out_file,"w"))==NULL)
			{printf("Can't open Sediment File : %s \n",sed_out_file);
			exit(EXIT_FAILURE);}
			printf("SEDIMENT_OUT       %s \n",sed_out_file);
		}
		
		/* Reading in the time-series grid names											*/ 
		if(strcmp(file_id,"WATER_DEPTH") == 0) 
		{
			ch=fscanf(project_file_fptr,"%s",dname);
			printf("WATER_DEPTH              %s \n",&dname);
		}
		if(strcmp(file_id,"RAINFALL") == 0)
		{
			ch=fscanf(project_file_fptr,"%s",rname);
			printf("RNAME              %s \n",&rname);
		}
		if(strcmp(file_id,"INF_DEPTH") == 0)
		{
			ch=fscanf(project_file_fptr,"%s",vinfname);
			printf("INF_DEPTH          %s \n",&vinfname);
		}
		if(strcmp(file_id,"SAND_FLUX_OUT") == 0)
		{
			ch=fscanf(project_file_fptr,"%s",sandfluxname);
			printf("SAND_FLUX_OUT      %s \n",&sandfluxname);
		}
		if(strcmp(file_id,"SILT_FLUX_OUT") == 0)
		{
			ch=fscanf(project_file_fptr,"%s",siltfluxname);
			printf("SILT_FLUX_OUT      %s \n",&siltfluxname);
		}
		if(strcmp(file_id,"CLAY_FLUX_OUT") == 0)
		{
			ch=fscanf(project_file_fptr,"%s",clayfluxname);
			printf("CLAY_FLUX_OUT      %s \n",&clayfluxname);
		}
		if(strcmp(file_id,"TOTAL_FLUX_OUT") == 0)
		{
			ch=fscanf(project_file_fptr,"%s",totalfluxname);
			printf("TOTAL_FLUX_OUT     %s \n",&totalfluxname);
		}
		if(strcmp(file_id,"SAND_MFAC_OUT") == 0)
		{
			ch=fscanf(project_file_fptr,"%s",sandMFACname);
			printf("SAND_MFAC_OUT      %s \n",&sandMFACname);
		}
		if(strcmp(file_id,"SILT_MFAC_OUT") == 0)
		{
			ch=fscanf(project_file_fptr,"%s",siltMFACname);
			printf("SILT_MFAC_OUT      %s \n",&siltMFACname);
		}
		if(strcmp(file_id,"CLAY_MFAC_OUT") == 0)
		{
			ch=fscanf(project_file_fptr,"%s",clayMFACname);
			printf("CLAY_MFAC_OUT      %s \n",&clayMFACname);
		}
		if(strcmp(file_id,"TOTAL_MFAC_OUT") == 0)
		{
			ch=fscanf(project_file_fptr,"%s",totalMFACname);
			printf("TOTAL_MFAC_OUT     %s \n",&totalMFACname);
		}
		if(strcmp(file_id,"SED_CONC") == 0)
		{
			ch=fscanf(project_file_fptr,"%s",cname);
			printf("SED_CONC              %s \n",&cname);
		}
		if(strcmp(file_id,"SUS_SED") == 0)
		{
			ch=fscanf(project_file_fptr,"%s",susname);
			printf("SUS_SED            %s \n",&susname);
		}
		if(strcmp(file_id,"EROS_DEP") == 0)
		{
			ch=fscanf(project_file_fptr,"%s",erosdepname);
			printf("EROS_DEP              %s \n",&erosdepname);
		}
	}

	}while(ch != EOF); 

	if((debug =fopen("debug.txt","w"))==NULL)
	{printf("Can't open debug File \n");
	exit(EXIT_FAILURE);}


	printf("Successfully Read all data from the Project File \n"); 
	fclose(project_file_fptr);

}

/*extern void FRTP(char *FileID, char *ProjectFileName, 
															FILE *FileHandler, char *FileName)
{
	int string;
	if(strcmp(FileID,ProjectFileName) == 0) 
		{
			string=fscanf(project_file_fptr,"%s",FileName);
			if((FileHandler=fopen(FileName,"r"))==NULL)
			{
				printf("Can't Open File : %s \n",FileName);
				exit(EXIT_FAILURE);
			}
			printf("%s          %s \n",ProjectFileName,FileName);
		}

}

		if(strcmp(file_id,"ELEVATION") == 0) 
		{
			ch=fscanf(project_file_fptr,"%s",elev_file);
			if((elev_file_fptr=fopen(elev_file,"r"))==NULL)
			{printf("Can't open Elevation File : %s \n",elev_file);
			 exit(EXIT_FAILURE);}
			printf("ELEVATION          %s \n",elev_file);
		}*/ 