						/*******************************/ 
						/*         CompVolumes.c       */ 
						/*******************************/ 


#include "all.h"

extern void CompInitialVol()

{
	int j,k;
	float wch, dch, sslope, tw_ch, area_ch, vol_ch;

	for(j=1;j<=m;j++)
	{
		for(k=1;k<=n;k++)
		{
			if(ishp[j][k] != nodatavalue)
			{
				if(chancheck == 1 && link[j][k] > 0)
				{
					wch = chp[link[j][k]][node[j][k]][2];
					dch = chp[link[j][k]][node[j][k]][3];
					sslope = chp[link[j][k]][node[j][k]][4];

					if(hch[j][k] < dch)
					{
					 tw_ch = wch + 2*hch[j][k]*sslope;
					 area_ch = (tw_ch + wch)/2 * hch[j][k];
					 vol_ch = area_ch * w * chp[link[j][k]][node[j][k]][6];
					}
					else
					{
					 tw_ch = wch + 2*dch*sslope;
					 area_ch = (tw_ch + wch)/2 * dch;
					 area_ch = area_ch + (hch[j][k] - dch)*tw_ch;
					 vol_ch = area_ch * w * chp[link[j][k]][node[j][k]][6];
					}

					init_ch_vol = init_ch_vol + vol_ch;
					tw_ch = wch + 2*dch*sslope;
					init_ov_vol = init_ov_vol + (w-tw_ch)*w*h[j][k];
				}
				else
				{
				 init_ov_vol = init_ov_vol + h[j][k]*w*w;
				}
			}
		}
	}
}
	   		 /********************************/ 
		 		 /* COMPUTE FINAL STORAGE VOLUME */ 
		 		 /********************************/ 
extern void CompFinalVol()
{		 		 
	int j,k;
	float wch, dch, sslope, tw_ch, area_ch, vol_ch;

	for(j=1;j<=m;j++)
	{
		for(k=1;k<=n;k++)
		{
			if(ishp[j][k] != nodatavalue)
			{
				if(chancheck == 1 && link[j][k] > 0)
				{
					wch = chp[link[j][k]][node[j][k]][2];
					dch = chp[link[j][k]][node[j][k]][3];
					sslope = chp[link[j][k]][node[j][k]][4];

					if(hch[j][k] < dch)
					{
					 tw_ch = wch + 2*hch[j][k]*sslope;
					 area_ch = (tw_ch + wch)/2 * hch[j][k];
					 vol_ch = area_ch * w * chp[link[j][k]][node[j][k]][6];
					}
					else
					{
					 tw_ch = wch + 2*dch*sslope;
					 area_ch = (tw_ch + wch)/2 * dch;
					 area_ch = area_ch + (hch[j][k] - dch)*tw_ch;
					 vol_ch = area_ch * w * chp[link[j][k]][node[j][k]][6];
					}

					final_ch_vol = final_ch_vol + vol_ch;
					tw_ch = wch + 2*dch*sslope;
					final_ov_vol = final_ov_vol + (w-tw_ch)*w*h[j][k];
				}
				else
				{
				 final_ov_vol = final_ov_vol + h[j][k]*w*w;
				}
			}
		}
	}
}