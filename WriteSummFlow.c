						/*******************************/ 
						/*        WriteSummFlow.c      */ 
						/*******************************/ 


#include "all.h"

extern void WriteSummFlow()
{

	double PercentFlow,InitialVol,FinalVol,InVolume,OutVolume;

	InitialVol = init_ch_vol   +  init_ov_vol;
	FinalVol   = final_ch_vol  +  final_ov_vol;
	InVolume  = InitialVol + vin;
	OutVolume = vinftot + vout + FinalVol;

	PercentFlow =	100.0 * (InVolume - OutVolume) / InVolume;

	/* ... summary of Output Flow */ 

	fprintf(Summ_file_fptr,
														"\nSUMMARY OF FLOW OUTPUT\n");
	fprintf(Summ_file_fptr,"======================\n\n");

	fprintf(Summ_file_fptr,
		"Peak Discharge (m3/s)......................................=");
	fprintf(Summ_file_fptr,"%15.2f \n",	qpeak);

	fprintf(Summ_file_fptr,
		"Time to Peak (min).........................................=");
	fprintf(Summ_file_fptr,"%15.2f \n",tpeak);

	fprintf(Summ_file_fptr,
		"Initial Surface Volume (m3)................................=");
	fprintf(Summ_file_fptr,"%15.2f \n",	InitialVol);

	fprintf(Summ_file_fptr,
		"Volume of Rainfall - retention (m3)........................=");
	fprintf(Summ_file_fptr,"%15.2f \n",	vin);

	fprintf(Summ_file_fptr,
		"Volume leaving the Watershed (m3)..........................=");
	fprintf(Summ_file_fptr,"%15.2f \n",vout);

	fprintf(Summ_file_fptr,
		"Percentage of Vout to Vin..................................=");
	fprintf(Summ_file_fptr,"%15.2f \n",(vout/vin)*100.0);

	fprintf(Summ_file_fptr,
		"Final Surface Volume (m3)..................................=");
	fprintf(Summ_file_fptr,"%15.2f \n",	FinalVol);

	fprintf(Summ_file_fptr,
		"Volume Infiltrated (m3)....................................=");
	fprintf(Summ_file_fptr,"%15.2f \n",vinftot);

	fprintf(Summ_file_fptr,
		"Percentage of Vinftot to Vin...............................=");
	fprintf(Summ_file_fptr,"%15.2f \n",	(vinftot/vin)*100.0);

	fprintf(Summ_file_fptr,
		"Percent Mass Balance...................................... =");
	fprintf(Summ_file_fptr,"%15.2f\n",PercentFlow);


	fprintf(Summ_file_fptr,
		"\nHYDROLOGICAL VARIABLES MINIMUM AND MAXIMUM VALUES\n");
	fprintf(Summ_file_fptr,
		"==================================================\n\n");

	fprintf(Summ_file_fptr,
		"Min. Rainfall Intensity (mm/hr)............................=");
	fprintf(Summ_file_fptr,"%15.2f \n",	aminrain*3600.*1000);

	fprintf(Summ_file_fptr,
		"Max. Rainfall Intensity (mm/hr)............................=");
	fprintf(Summ_file_fptr,"%15.2f \n",	amaxrain*3600.*1000);

	fprintf(Summ_file_fptr,
		"Min. Infiltration Depth (mm)...............................=");
	fprintf(Summ_file_fptr,"%15.2f \n",	aminvinf*1000);

	fprintf(Summ_file_fptr,
		"Max. Infiltration Depth (mm)...............................=");
	fprintf(Summ_file_fptr,"%15.2f \n",	amaxvinf*1000);

	fprintf(Summ_file_fptr,
		"Min. Overland Depth (m)....................................=");
	fprintf(Summ_file_fptr,"%15.2f \n",amindepth);

	fprintf(Summ_file_fptr,
		"Max. Overland Depth (m)....................................=");
	fprintf(Summ_file_fptr,"%15.2f \n",amaxdepth);

	fprintf(Summ_file_fptr,
		"Min. Channel Depth (m).....................................=");
	fprintf(Summ_file_fptr,"%15.2f \n",	amincdepth);

	fprintf(Summ_file_fptr,
		"Max. Channel Depth (m).....................................=");
	fprintf(Summ_file_fptr,"%15.2f \n\n",amaxcdepth);

}