						/*******************************/ 
						/*         ReadGrids.c         */ 
						/*******************************/ 


#include "all.h"

			/**********************************/ 
			/*     FCT: ReadGridHeaders       */ 
			/**********************************/ 

extern void ReadGridHeaders()
{

	/* Variables that will hold the ASCII grids header information	*/ 
	char nrows_label[15], ncols_label[15], xllcorner_label[15], 
		yllcorner_label[15], cellsize_label[15], nodatavalue_label[15],
		h_label[7][80];
	int  head,i;
	float h_value[7];

	/* Read the shape ASCII grid header to get project info					*/ 
	/* the "header" variable will be used to hold the header info		*/ 

	fprintf(Summ_file_fptr,"\nASCII grid files header  \n");
	fprintf(Summ_file_fptr,"------------------------- \n");
	fscanf(shap_file_fptr,"%s %i",&ncols_label, &n);
	fscanf(shap_file_fptr,"%s %i",&nrows_label, &m);
	fscanf(shap_file_fptr,"%s %f",&xllcorner_label, &xllcorner);
	fscanf(shap_file_fptr,"%s %f",&yllcorner_label, &yllcorner);
	fscanf(shap_file_fptr,"%s %f",&cellsize_label, &w);
	fscanf(shap_file_fptr,"%s %i",&nodatavalue_label, &nodatavalue);

	/* Do not use the xxxx_label variables because I want to				*/ 
	/* make sure that the user entered them in the right order.			*/ 

	head  = sprintf( header,        "ncols\t\t%i\n", n );
	head += sprintf( header + head, "nrows\t\t%i\n", m  );
	head += sprintf( header + head, "xllcorner\t%.2f\n", xllcorner);
	head += sprintf( header + head, "yllcorner\t%.2f\n", yllcorner);
	head += sprintf( header + head, "cellsize\t%.2f\n", w);
	head += sprintf( header + head, "NODATA_value\t%i\n", 
																										nodatavalue);
	
	fprintf(Summ_file_fptr,header);

	/* Need to read the rest of the input grids headers							*/ 
	for (i=1;i<=6;i++)
	 {
		 if(elev_file_fptr)
			 fscanf(elev_file_fptr,"%s %f",&h_label[i], &h_value[i]);
		 else
		 {
			 printf(" Elevation grid doesn't exist. Pease, define one\n");
			 exit(EXIT_FAILURE);
		 }

		 if(nsoil > 1)
		 {
			 if(soil_file_fptr)
				 fscanf(soil_file_fptr,"%s %f",&h_label[i], &h_value[i]);
			 else
			 {
				 printf("\n\nYou have defined more than one soil type");
				 printf("\nYou need to define a soil type grid\n\n");
				 exit(EXIT_FAILURE);
			 }
		 }

		 if(nman > 1)
		 {
			 if(iman_file_fptr)
				 fscanf(iman_file_fptr,"%s %f",&h_label[i], &h_value[i]);
			 else
			 {
				 printf("\n\nYou have defined more than one land use type");
				 printf("\nYou need to define a land use type grid\n\n");
				 exit(EXIT_FAILURE);
			 }
		 }

		 if(chancheck == 1)
		 {
			 if(node_file_fptr)
				 fscanf(node_file_fptr,"%s %f",&h_label[i], &h_value[i]);
			 else
			 {
				 printf("\n\nYou have selected the channel routing option");
				 printf("\nYou need to define a node number grid\n\n");
				 exit(EXIT_FAILURE);
			 }

			 if(link_file_fptr)
				 fscanf(link_file_fptr,"%s %f",&h_label[i], &h_value[i]);
			 else
			 {
				 printf("\n\nYou have selected the channel routing option");
				 printf("\nYou need to define a link number grid\n\n");
				 exit(EXIT_FAILURE);
			 }

		 }

		 if(indexsdep == 1)
		 {
			 if(sdep_file_fptr)
				 fscanf(sdep_file_fptr,"%s %f",&h_label[i], &h_value[i]);
			 else
			 {
				 printf("\n\nYou have selected the retention depth option");
				 printf("\nYou need to define a retention depth grid\n\n");
				 exit(EXIT_FAILURE);
			 }
		 }
	 }

}

			/**********************************/ 
			/*         ReadInputGrids         */ 
			/**********************************/ 

extern void ReadInputGrids()
{
	int j,k;

	ncells = 0; 

	for(j=1;j<=m;j++)
	{
		for(k=1;k<=n;k++)
		{
			fscanf(shap_file_fptr,"%ld ",&ishp[j][k]); 

			if(ishp[j][k] != nodatavalue) ncells++;

			fscanf(elev_file_fptr,"%f ",&e[j][k]);
			e[j][k] = e[j][k] / elconv;

			if(nsoil > 0)
			{
				if(nsoil == 1)
				{
					isoil[j][k] = 1;
				}
				else
				{
					fscanf(soil_file_fptr,"%ld ",&isoil[j][k]);
				}
			}

			if(nman == 1)
			{
				iman[j][k] = 1;
			}
			else
			{
				fscanf(iman_file_fptr,"%ld ",&iman[j][k]); 
			}

			if(chancheck == 1)
			{
				fscanf(node_file_fptr,"%ld",&node[j][k]);
				fscanf(link_file_fptr,"%ld",&link[j][k]);
			}

			if(indexsdep == 1) fscanf(sdep_file_fptr,"%f",&sdep[j][k]);
		}
	}

	/* Input ASCII grids .... read																	*/ 
	fprintf(Summ_file_fptr,
											 "\nThe following Grids have been read: \n");
	fprintf(Summ_file_fptr," ------------------------------- \n");
	fprintf(Summ_file_fptr,"Elevation Grid: %s \n", elev_file);
	fprintf(Summ_file_fptr,"Shape Grid: \t%s \n", shap_file);
	fprintf(Summ_file_fptr,"Soils Grid: \t%s \n", soil_file);
	fprintf(Summ_file_fptr,"Landuse Grid: \t%s \n", iman_file);
	fprintf(Summ_file_fptr,"Node Grid: \t%s \n", node_file);
	fprintf(Summ_file_fptr,"Link Grid: \t%s \n\n", link_file);  
	printf("Successfully Read Input Grid Data \n");
	fprintf(Summ_file_fptr,"Number of cells in basin: %i\n", ncells); 
	fprintf(Summ_file_fptr,"Basin area: %.3f [ha]\n", ncells*w*w/10000); 

	fclose(elev_file_fptr);
	fclose(shap_file_fptr);
	if(nsoil > 1)	fclose(soil_file_fptr);
	if(nman > 1) fclose(iman_file_fptr);
	if(chancheck == 1)
	{
		fclose(node_file_fptr);
		fclose(link_file_fptr);
	}
	if(indexsdep == 1) fclose(sdep_file_fptr);

}