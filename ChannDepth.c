						/*******************************/ 
						/*         ChannDepth.c        */ 
						/*******************************/ 


#include "all.h"

extern void ChannDepth()
{
	int ic,j,l,k,jj;
	float wch, dch,sfactor, sdep_ov, inflowVol,vol_ov_in;

	for(ic=1;ic<=maxlink;ic++)
	{
	 for(l=1;l<=nchan_node[ic];l++)
	 {
		 wch = chp[ic][l][2];
		 dch = chp[ic][l][3];
		 sfactor = chp[ic][l][6];

		 j = ichn[ic][l][1];	
		 k = ichn[ic][l][2];
		 jj = ichn[ic][l+1][1];

		 /* Channel depths are updated at each link and node except		*/ 
		 /* for the last node of the link because the last node of		*/ 
		 /* one link is the same as the first node of the next link		*/ 
		 /* In the outlet link, we update depth in all the nodes			*/ 
		 /* NOTE: To understand the condition of (j > 0 && jj >= 0)		*/ 
		 /*		look at the CASC2D summary output file, where it says :	*/ 
		 /*		Channel Linkage Information															*/ 

		 if(j > 0 && jj >= 0)
		 {
			 /* Find new channel depth after adding inflow volume				*/ 
			 
			 inflowVol = dqch[j][k]*dt;
			 
			 /* ... and the volume coming from the overland	(vol_ov_in) */ 
			 
			 if(sdep[j][k] > dch)
				 sdep_ov = sdep[j][k] - dch;
			 else
				 sdep_ov = 0.0;
			
			 vol_ov_in = 0;

			 if(h[j][k] > sdep_ov)
			 {
				 vol_ov_in = (h[j][k] - sdep_ov)*w*w;				 
				 h[j][k] = sdep_ov;
			 }

			 hch[j][k] = newChnDepth(wch,dch,sfactor,j,k,
															(inflowVol + vol_ov_in));

			 /* Determining the Minimum and the Maximum Channel Depths	*/ 

			 if(hch[j][k] < amincdepth) amincdepth = hch[j][k];
			 if(hch[j][k] > amaxcdepth) amaxcdepth = hch[j][k];

			 /* Negative Depth in the Channel --> EXIT program					*/ 

			 if (hch[j][k] < 0.0)
			 {
				 if (hch[j][k] < 0.0 && hch[j][k] > -0.001) 
					 hch[j][k] = 0.0;
				 else 
					 {
							fprintf(Summ_file_fptr,
							 "Channel Negative Depth:row = %ld column = %ld \n",
																															j,k);
							fprintf(Summ_file_fptr,
							 "Depth at link = %ld, node = %ld is %.8f meters\n",
																									ic,l, hch[j][k]);
							RunTime(clock());

							GridsMemFree();

							exit(0);
					 }
			 }

			 dqch[j][k] = 0.0;

		 }  /* end of : if(j > 0 && jj >= 0)  */ 
	 }	/* end of : for(l=1;l<=nchan_node[ic];l++)  */ 
	}	/* end of : for(ic=1;ic<=maxlink;ic++)  */ 
}