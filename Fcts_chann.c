						/*******************************/ 
						/*         Fcts_chann.c        */ 
						/*******************************/ 

#include "all.h"

			/**********************************/ 
			/*         FUNCT: newChnDepth     */ 
			/**********************************/ 

extern float newChnDepth(float wch,float dch,float sfactor,
												 int j, int k,float addedVolume)
{
	float area_ch,vol_ch,area_init,vol_init,
		vol_final,newdepth;

	/* Channel area and volume																			*/ 
	
	area_ch = wch * dch;
	vol_ch = area_ch * w * sfactor;

	/* Calculates initial area and volume														*/ 
	
	if(hch[j][k] <= dch)
	 area_init =  wch * hch[j][k];
	else
	 area_init = (hch[j][k] - dch) * w + area_ch;

	vol_init = area_init * w * sfactor;

	/* After adding new volume calculates volume										*/ 
	
	vol_final = vol_init + addedVolume;

	/* ... and depth corresponding to the final volume							*/ 
	
	if(vol_final > vol_ch)
	 newdepth = dch + (vol_final - vol_ch) / (w*w*sfactor);
	else
	 newdepth = vol_final / (wch*w*sfactor);

	return(newdepth);

}

			/**********************************/ 
			/*         FUNCT: chnDischarge    */ 
			/**********************************/ 

/* Calculates the outflow in m3/s from a cell */ 

float chnDischarge(float hchan,float hh,float wch,float dch,
					float stordep,float rmanch,float a,float sf,float sfactor)
{
	float area, wp, dQ, vol_ch_avail;

	/* Calculates flow area and wetted perimeter										*/ 
	
	if(hchan <= dch)
	 {
		 area = wch * hh;
		 wp = (float)(wch + 2 * hh);
	 }
	 else
	 {
		 area = wch * (dch - stordep) + w * (hchan-dch);
		 wp = (float)(wch+2*(dch-stordep) + 2*(w-wch) + 2*(hchan-dch));
	 }

	dQ = (float)(a*(sqrt(fabs(sf))/rmanch)*
													(pow(area,1.6667))/(pow(wp,0.6667)));
			 
	/* Limit the outflow by availability														*/ 
	
	vol_ch_avail = area * w * sfactor;	

	if(dQ*dt > vol_ch_avail) dQ = vol_ch_avail/dt;

	return(dQ);

}

