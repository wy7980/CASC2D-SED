						/*******************************/ 
						/*         ChannRout.c         */ 
						/*******************************/ 


#include "all.h"

			/**********************************/ 
			/*         FUNCT: ChannRout       */ 
			/**********************************/ 

extern void ChannRout()
{
	int ic,l;

	for(ic=1;ic<=maxlink;ic++)
	{
		for(l=1;l<=nchan_node[ic];l++)
		{
			/*  Note :	When ichn[ic][l+1][1] is less than zero,				*/ 
			/*					then that	indicates that the channel 						*/ 
			/*				  routing for the current link is complete.				*/
			/*					There is no routing for the outlet cell					*/ 
			
			if(ichn[ic][l+1][1] > 0)
			{
			 chnchn(ic,l);
			}

		} /* end For loop for the nodes in the link */ 
	} /* end For loop for the links  */ 
}

			/**********************************/ 
			/*         FUNCT: chnchn          */ 
			/**********************************/ 

extern void chnchn(int ic,int l)
{

	float a = 1.0;
	float vel = 0.0;
	float wch,dch,sslope,rmanch,sfactor,so, sf, hh, dhdx, 
		    dq, stordep, hchan,dq_ov; 
		
	int  j,k,jj,kk,jjj,iic, ijun, ill;
	
	/* row and column of link IC and node l													*/ 
	
	j = ichn[ic][l][1];
	k = ichn[ic][l][2];
	
	/* row and column of following node in link IC									*/ 
	
	jj = ichn[ic][l+1][1];
	kk = ichn[ic][l+1][2];

	/* Note : JJJ is a check to see when the end of									*/	
	/*        a channel link has been reached.											*/ 
	
	jjj = ichn[ic][l+2][1];

	/* Channel characteristics :																		*/ 

	wch = chp[ic][l][2];			/* width								*/ 
	dch = chp[ic][l][3];			/* depth								*/ 
	sslope = chp[ic][l][4];		/* side slope						*/ 
	rmanch = chp[ic][l][5];		/* manning's n					*/ 
	sfactor = chp[ic][l][6];	/* sinuosity factor			*/ 
	stordep = sdep[j][k];			/* Storage depth				*/ 
	hchan = hch[j][k];				/* Channel water depth	*/ 
	hh = hch[j][k] - stordep;	

	/*if(fabs(hh) < 1e-4) hh=0.0;	 check for negligible water depth */ 

	/* Channel slope																								*/ 
	
	so = (e[j][k] - e[jj][kk])/(w*sfactor);

	dq_ov = 0.0;
	
	/* If jjj<0, then the end of the channel link has been reached.	*/ 
	/* Slope is computed with last node of current link and first		*/ 
	/*  node of following one																				*/ 
	
	if(jjj < 0)
	{
		for (iic=1;iic<=maxlink;iic++)
		{
			if(jj == ichn[iic][1][1] && kk == ichn[iic][1][2])
			{
				so = (e[j][k] - dch - e[jj][kk] + chp[iic][1][3])/(w*sfactor);
				ijun = iic;
			}
		}
	}

	dhdx = (hch[jj][kk] - hch[j][k])/(w*sfactor);

	sf = (float)(so - dhdx + 1e-30);

	/* Nota de Jorge: Sf se deberia quedar con el mismo signo */ 
	if(fabs(sf) < 1e-20) sf = (float)(1e-20);  

	if (sf < 0.0) 
	{
		a = (float)(-1.0*a);

		if (jjj < 0)
		{ 
			/* Take channel chars. of the 1st node of downstream link */ 
			
			wch = chp[ijun][1][2];
			dch = chp[ijun][1][3];
			sslope = chp[ijun][1][4];
			rmanch = chp[ijun][1][5];
			sfactor = chp[ijun][1][6];
		}
		else
		{ 
			/*Take channel chars. of the next node within current link */ 
			 
			wch = chp[ic][l+1][2];
			dch = chp[ic][l+1][3];
			sslope = chp[ic][l+1][4];
			rmanch = chp[ic][l+1][5];
			sfactor = chp[ic][l+1][6];
		}

		stordep = sdep[jj][kk];
		hchan = hch[jj][kk];
		hh = hch[jj][kk] - stordep;	

		/*if(fabs(hh) < 1e-4) hh = 0.0;check for negligible  depth		*/ 
	}

	/* Determining discharge 																				*/ 
	
	dq = chnDischarge(hchan,hh,wch,dch,stordep,rmanch,a,sf,sfactor);

	/* Transfer flow from cell (j,k) to (jj,kk)											*/ 
	
	dqch[j][k] = dqch[j][k] - dq;
	dqch[jj][kk] = dqch[jj][kk] + dq;

	/* If (j,k) is a printout flow discharge internal location			*/ 
	
	for (ill=1;ill<=ndis;ill++)
	{
		if(j == iq[ill][1] && k == iq[ill][2]) q[ill] = dq;
	}

	/* Channel sediment routing																			*/ 
	
	if(indexeros == 1 && dq != 0.0 && hchan !=0)
	{
		if(a >= 0.0)
		{
			RoutSedChn(dq,sf,j,k,jj,kk,wch,hchan);
		}
		else
		{
			RoutSedChn(-dq,-sf,jj,kk,j,k,wch,hchan);
		}
	}

}		/* End of CHNCHN */ 

	

