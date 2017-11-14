						/*******************************/ 
						/*        ReadChannFile.c      */ 
						/*******************************/ 


#include "all.h"

extern void ReadChannFile()
{
	char ch;
	int j,k;

	printf("Reading Channel Data \n");

	do{ 
	 ch=fscanf(chn_file_fptr,"%ld",&nchan_link);
	 ch=fscanf(chn_file_fptr,"%ld",&nchan_node[nchan_link]);

	 for(k=1;k<=nchan_node[nchan_link];k++)
	 {
		 for(j=1;j<=6;j++)
		 {
			 ch=fscanf(chn_file_fptr,"%f ",&chp[nchan_link][k][j]);
		 }
	 } 

	} while(ch!=EOF);

	maxlink = nchan_link;

	/* Writing Channel Information to Output Summary File						*/
	
/*	fprintf(Summ_file_fptr,"\n Channel Input Data \n");
	fprintf(Summ_file_fptr," ------------------ \n");
	for(i=1;i<=maxlink;i++)
	{
		for(k=1;k<=nchan_node[i];k++)
		{
			for(j=1;j<=6;j++)
			{
				fprintf(Summ_file_fptr,"CHP[%ld][%ld][%ld] = %f ",
																			i,k,j,chp[i][k][j]);
			}
			fprintf(Summ_file_fptr,"\n");
		}
	}
*/

	printf("Successfully Read Channel Data \n");
	fclose(chn_file_fptr);

}