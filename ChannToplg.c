						/*******************************/ 
						/*         ChannToplg.c        */ 
						/*******************************/ 


#include "all.h"

extern void ChannToplg()
{

	int maxchn = 1; 
	int downstream[50],upstream1[50],upstream2[50],
			ic,l,rr,cc,ll,rc,i,j,k, p,q,ro,co,outlink,outnode;
	float elev;

	outlink = link[jout][kout];
	outnode = node[jout][kout];
	/* Determining Row and Column Locations													*/ 

	for(j=1;j<=m;j++)
	{
		for(k=1;k<=n;k++)
		{
			if(link[j][k] !=0 && node[j][k] !=0)
			{
				ichn[link[j][k]][node[j][k]][1] = j;
				ichn[link[j][k]][node[j][k]][2] = k;
			
				if(maxchn < node[j][k]) maxchn = node[j][k];
			}
		}
	}

	/* NOTE: because the last node of one link and the first node		*/ 
	/* of the downstream link is the same, the number of nodes of		*/ 
	/* one link is the last numbered node in the link plus one			*/															
	maxchn = maxchn + 2;  /* Maximum number of nodes + 1			  		*/ 

	/* Determining Downstream and Upstream Linkages									*/ 
	for(i=1;i<=maxlink;i++)
	{
		downstream[i] = 0;
		upstream1[i] = 0;
		upstream2[i] = 0;
	}

	for(i=1;i<=maxlink;i++)
	{
		rr = ichn[i][1][1];
		cc = ichn[i][1][2];

		/* Checking North																							*/ 

		if(rr-1 >= 1)
		{
			ll = link[rr-1][cc];
			
			if(ll !=0 && ll != i)
			{
				if(upstream1[i] == 0)
				{
					upstream1[i] = ll;
				}
				else
				{
					upstream2[i] = ll;
				}
				downstream[ll] = i;
			}
		}

		/* Checking South																							*/ 

		if(rr+1 <= m)
		{
			ll = link[rr+1][cc];
			
			if(ll !=0 && ll != i)
			{
				if(upstream1[i] == 0)
				{
					upstream1[i] = ll;
				}
				else
				{
					upstream2[i] = ll;
				}
				downstream[ll] = i;
			}
		}

		/* Checking West																							*/ 

		if(cc-1 >= 1)
		{
			ll = link[rr][cc-1];
			
			if(ll !=0 && ll != i)
			{
				if(upstream1[i] == 0)
				{
					upstream1[i] = ll;
				}
				else
				{
					upstream2[i] = ll;
				}
				downstream[ll] = i;
			}
		}

		/* Checking East																							*/ 

		if(cc+1 <= n)
		{
			ll = link[rr][cc+1];
			
			if(ll !=0 && ll != i)
			{
				if(upstream1[i] == 0)
				{
					upstream1[i] = ll;
				}
				else
				{
					upstream2[i] = ll;
				}

				downstream[ll] = i;
			}
		}
	}

	/*Adding the downstream Row and Column to the end of every Link */ 

	for(i=1;i<=maxlink;i++)
	{
		rc = 0;

		for(j=1;j<=maxchn;j++)
		{
			if(i != outlink)
			{
				if(ichn[i][j][1] == 0 && rc == 0)
				{
					if(ichn[i][j-1][1] > 0) 
					{
						ll = downstream[i];
						
						ichn[i][j][1] = ichn[ll][1][1];
						ichn[i][j][2] = ichn[ll][1][2];
					}
					rc = 1;
				}
			}
		}		
	}
  
	/* Adding a -1 to the end of every link except for the outlet		*/ 
	/* link																													*/ 
	
	for(i=1;i<=maxlink;i++)
	{
		for(k=1;k<=2;k++)
		{
			for(j=1;j<=maxchn;j++)
			{
				if(i != outlink)
				{
					if(ichn[i][j][k] == 0)
					{
						if(ichn[i][j-1][k] > 0) ichn[i][j][k] = -1;
					}
				}
			}
		}
	}
	
	/* Writing channel network info and topology to summary file		*/ 

	printf("Number of Channels         = %ld \n",maxlink);
	printf("Maximum Length of Channels = %ld \n",maxchn);

	fprintf(Summ_file_fptr,"\nChannel Linkage Information\n");
	fprintf(Summ_file_fptr,"---------------------------\n\n");

	fprintf(Summ_file_fptr,"Maximum Number of Links = %ld \n",
																									maxlink);
	fprintf(Summ_file_fptr,"Maximum Number of Nodes = %ld \n\n",
																									 maxchn);

	for(i=1;i<=maxlink;i++)
	{
		for(k=1;k<=2;k++)
		{
			for(j=1;j<=maxchn;j++)
			{
				if(j<maxchn)
				{
					fprintf(Summ_file_fptr,"%5ld",ichn[i][j][k]);
				}
				else
				{
					fprintf(Summ_file_fptr,"%5ld \n",ichn[i][j][k]);
				}
			}
		}

		fprintf(Summ_file_fptr,"\n");
	}

	fprintf(Summ_file_fptr,
					" Link    Downstream    Upstream1   Upstream2 \n\n");
			    
	for(i=1;i<=maxlink;i++)
	{
		fprintf(Summ_file_fptr,"%4ld %10ld  %10ld  %10ld \n",
										i,downstream[i],upstream1[i],upstream2[i]);
	
		printf("%4ld %10ld  %10ld  %10ld \n",
										i,downstream[i],upstream1[i],upstream2[i]);					
	} 
	
	/* Mask grid value equal to 2 if channel going through it				*/ 
	for(ic=1;ic<=maxlink;ic++)
	{
		for(l=1;l<=maxchn;l++)
		{
			j=ichn[ic][l][1];
			k=ichn[ic][l][2];

			if(j > 0 && chancheck == 1)
			{
			 ishp[j][k] = 2;
			}
		}
	}
	
	
	/* Channel characteristics at the outlet												*/ 
	wchout = chp[outlink][outnode][2];
	dchout = chp[outlink][outnode][3];
	rmanout = chp[outlink][outnode][5];
	sfactorout = chp[outlink][outnode][6];
	for(p=-1; p<=1; p++)
	{
		for(q=-1; q<=1; q++)
		{
			ro = jout + p;
			co = kout + q;
			if(ro>0 && ro<=m && co>0 && co<=n && ro!=jout && co!=kout)
				if(ishp[ro][co] == 2 ) elev = e[ro][co];
		}
	}
	sout = (float)(fabs(elev - e[jout][kout] )/ w);


}