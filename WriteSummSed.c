						/*******************************/
						/*        WriteSummSed.c       */
						/*******************************/


#include "all.h"

extern void WriteSummSed()
{

	double PercentSed,TotRemOvr,TotRemChn,TotEroded,TotLeaving,
				TotSusRemOvr,TotDepRemOvr,TotSusRemChn,TotDepRemChn;

	struct gstats totnetv_stats;

	totnetv_stats = gridstats(totnetv);

	TotEroded    = fabs(tot_eroded[1]+tot_eroded[2]+tot_eroded[3]);
	TotSusRemOvr = sus_ov[1] + sus_ov[2] + sus_ov[3];
	TotDepRemOvr = dep_ov[1]+dep_ov[2]+dep_ov[3];
	TotRemOvr    = tot_ov[1]+tot_ov[2]+tot_ov[3];
	TotSusRemChn = sus_ch[1]+sus_ch[2]+sus_ch[3];
	TotDepRemChn = dep_ch[1]+dep_ch[2]+dep_ch[3];
	TotRemChn    = tot_ch[1]+tot_ch[2]+tot_ch[3];
	TotLeaving   = sed_out[1]+sed_out[2]+sed_out[3];

	PercentSed = 100.0 * (TotLeaving + TotRemOvr + TotRemChn
												- TotEroded) / TotEroded ;

	/* ... summary of output sediment																*/ 

	fprintf(Summ_file_fptr,
		"\nSUMMARY OF SEDIMENT OUTPUT : Volume in Cubic Meters\n");
	fprintf(Summ_file_fptr,
		"(Percentages from the total eroded \n");
	fprintf(Summ_file_fptr,
		"===================================================\n\n");

	fprintf(Summ_file_fptr,
		"Total Volume of Sand Eroded................................=");
	fprintf(Summ_file_fptr,"%15.2f \n",fabs(tot_eroded[1]));

	fprintf(Summ_file_fptr,
		"Total Volume of Silt Eroded................................=");
	fprintf(Summ_file_fptr,"%15.2f \n",fabs(tot_eroded[2]));

	fprintf(Summ_file_fptr,
		"Total Volume of Clay Eroded................................=");
	fprintf(Summ_file_fptr,"%15.2f \n",fabs(tot_eroded[3]));

	fprintf(Summ_file_fptr,
		"Total Volume of Material Eroded............................=");
	fprintf(Summ_file_fptr,"%15.2f \n\n", TotEroded);


	fprintf(Summ_file_fptr,
	       "Volumes of Eroded Sediment Remaining on the Overland:\n");

	fprintf(Summ_file_fptr,
		"----------------------------------------------------\n");

	fprintf(Summ_file_fptr,
		"Total Volume of Suspended Sand.............................=");
	fprintf(Summ_file_fptr,"%15.2f -> %5.2f %% \n", 
											sus_ov[1],fabs(sus_ov[1]/tot_eroded[1]*100));

	fprintf(Summ_file_fptr,
		"Total Volume of Suspended Silt.............................=");
	fprintf(Summ_file_fptr,"%15.2f -> %5.2f %% \n", 
											sus_ov[2],fabs(sus_ov[2]/tot_eroded[2]*100));

	fprintf(Summ_file_fptr,
		"Total Volume of Suspended Clay.............................=");
	fprintf(Summ_file_fptr,"%15.2f -> %5.2f %% \n", 
											sus_ov[3],fabs(sus_ov[3]/tot_eroded[3]*100));

	fprintf(Summ_file_fptr,
		"Total Volume of Suspended Sediment.........................=");
	fprintf(Summ_file_fptr,"%15.2f -> %5.2f %% \n\n", 
										TotSusRemOvr,fabs(TotSusRemOvr/TotEroded*100));

	fprintf(Summ_file_fptr,
		"Total Volume of Deposited Sand.............................=");
	fprintf(Summ_file_fptr,"%15.2f -> %5.2f %% \n", 
											dep_ov[1],fabs(dep_ov[1]/tot_eroded[1]*100));

	fprintf(Summ_file_fptr,
		"Total Volume of Deposited Silt.............................=");
	fprintf(Summ_file_fptr,"%15.2f -> %5.2f %% \n", 
											dep_ov[2],fabs(dep_ov[2]/tot_eroded[2]*100));

	fprintf(Summ_file_fptr,
		"Total Volume of Deposited Clay.............................=");
	fprintf(Summ_file_fptr,"%15.2f -> %5.2f %% \n", 
											dep_ov[3],fabs(dep_ov[3]/tot_eroded[3]*100));

	fprintf(Summ_file_fptr,
		"Total Volume of Deposited Sediment.........................=");
	fprintf(Summ_file_fptr,"%15.2f -> %5.2f %% \n\n", 
										TotDepRemOvr,fabs(TotDepRemOvr/TotEroded*100));

	fprintf(Summ_file_fptr,
		"Total Volume of Sand Remaining on the Overland.............=");
	fprintf(Summ_file_fptr,"%15.2f -> %5.2f %% \n", 
											tot_ov[1],fabs(tot_ov[1]/tot_eroded[1]*100));

	fprintf(Summ_file_fptr,
		"Total Volume of Silt Remaining on the Overland.............=");
	fprintf(Summ_file_fptr,"%15.2f -> %5.2f %% \n", 
											tot_ov[2],fabs(tot_ov[2]/tot_eroded[2]*100));

	fprintf(Summ_file_fptr,
		"Total Volume of Clay Remaining on the Overland.............=");
	fprintf(Summ_file_fptr,"%15.2f -> %5.2f %% \n", 
											tot_ov[3],fabs(tot_ov[3]/tot_eroded[3]*100));

	fprintf(Summ_file_fptr,
		"Total Volume of Eroded Material Remaining on the Overland..=");
	fprintf(Summ_file_fptr,"%15.2f -> %5.2f %% \n\n", 
													TotRemOvr,fabs(TotRemOvr/TotEroded*100));

	fprintf(Summ_file_fptr,
		     "Volumes of Eroded Sediment Remaining in the Channels:\n");
	fprintf(Summ_file_fptr,
		      "----------------------------------------------------\n");

	fprintf(Summ_file_fptr,
		"Total Volume of Suspended Sand.............................=");
	fprintf(Summ_file_fptr,"%15.2f -> %5.2f %% \n", 
											sus_ch[1],fabs(sus_ch[1]/tot_eroded[1]*100));

	fprintf(Summ_file_fptr,
		"Total Volume of Suspended Silt.............................=");
	fprintf(Summ_file_fptr,"%15.2f -> %5.2f %% \n", 
											sus_ch[2],fabs(sus_ch[2]/tot_eroded[2]*100));

	fprintf(Summ_file_fptr,
		"Total Volume of Suspended Clay.............................=");
	fprintf(Summ_file_fptr,"%15.2f -> %5.2f %% \n", 
											sus_ch[3],fabs(sus_ch[3]/tot_eroded[3]*100));

	fprintf(Summ_file_fptr,
		"Total Volume of Suspended Sediment.........................=");
	fprintf(Summ_file_fptr,"%15.2f -> %5.2f %% \n\n", 
										TotSusRemChn,fabs(TotSusRemChn/TotEroded*100));

	fprintf(Summ_file_fptr,
		"Total Volume of Deposited Sand.............................=");
	fprintf(Summ_file_fptr,"%15.2f -> %5.2f %% \n", 
										 dep_ch[1],fabs(dep_ch[1]/tot_eroded[1]*100));

	fprintf(Summ_file_fptr,
		"Total Volume of Deposited Silt.............................=");
	fprintf(Summ_file_fptr,"%15.2f -> %5.2f %% \n", 
											dep_ch[2],fabs(dep_ch[2]/tot_eroded[2]*100));

	fprintf(Summ_file_fptr,
		"Total Volume of Deposited Clay.............................=");
	fprintf(Summ_file_fptr,"%15.2f -> %5.2f %% \n", 
											dep_ch[3],fabs(dep_ch[3]/tot_eroded[3]*100));

	fprintf(Summ_file_fptr,
		"Total Volume of Deposited Sediment.........................=");
	fprintf(Summ_file_fptr,"%15.2f -> %5.2f %% \n\n", 
									TotDepRemChn,fabs(TotDepRemChn/TotEroded*100));

	fprintf(Summ_file_fptr,
		"Total Volume of Sand Remaining in the Channels.............=");
	fprintf(Summ_file_fptr,"%15.2f -> %5.2f %% \n", 
											tot_ch[1],fabs(tot_ch[1]/tot_eroded[1]*100));

	fprintf(Summ_file_fptr,
		"Total Volume of Silt Remaining in the Channels.............=");
	fprintf(Summ_file_fptr,"%15.2f -> %5.2f %% \n", 
											tot_ch[2],fabs(tot_ch[2]/tot_eroded[2]*100));

	fprintf(Summ_file_fptr,
		"Total Volume of Clay Remaining in the Channels.............=");
	fprintf(Summ_file_fptr,"%15.2f -> %5.2f %% \n", 
											tot_ch[3],fabs(tot_ch[3]/tot_eroded[3]*100));

	fprintf(Summ_file_fptr,
		"Total Volume of Eroded Material Remaining in the Channels..=");
	fprintf(Summ_file_fptr,"%15.2f -> %5.2f %% \n\n", 
													TotRemChn,fabs(TotRemChn/TotEroded*100));

	fprintf(Summ_file_fptr,
		"Volumes of Eroded Sediment Leaving the Watershed:\n");
	fprintf(Summ_file_fptr,
		"----------------------------------------------------\n");

	fprintf(Summ_file_fptr,
		"Total Volume of Eroded Sand Leaving the Watershed..........=");
	fprintf(Summ_file_fptr,"%15.2f -> %5.2f %% \n", 
										sed_out[1],fabs(sed_out[1]/tot_eroded[1]*100));

	fprintf(Summ_file_fptr,
		"Total Volume of Eroded Silt Leaving the Watershed..........=");
	fprintf(Summ_file_fptr,"%15.2f -> %5.2f %% \n", 
										sed_out[2],fabs(sed_out[2]/tot_eroded[2]*100));

	fprintf(Summ_file_fptr,
		"Total Volume of Eroded Clay Leaving the Watershed..........=");
	fprintf(Summ_file_fptr,"%15.2f -> %5.2f %% \n", 
										sed_out[3],fabs(sed_out[3]/tot_eroded[3]*100));

	fprintf(Summ_file_fptr,
		"Total Volume of Eroded Material Leaving the Watershed......=");
	fprintf(Summ_file_fptr,"%15.2f -> %5.2f %% \n\n", 
												TotLeaving,fabs(TotLeaving/TotEroded*100));

	fprintf(Summ_file_fptr,
		"Percent Mass Balance.......................................=");
	fprintf(Summ_file_fptr,"%15.2f \n\n", PercentSed);


	/* ... Minimum and Maximum Values for Various Variables					*/ 

	fprintf(Summ_file_fptr,
		          "\nSEDIMENT VARIABLES MINIMUM AND MAXIMUM VALUES\n");
	fprintf(Summ_file_fptr,
		          "=============================================\n\n");

	fprintf(Summ_file_fptr,
		"Max. Flux Conc. Overland (m3/s/m3/s)......................=");
	fprintf(Summ_file_fptr,"\t%g \n", amaxFluxCoutOv);

	fprintf(Summ_file_fptr,
		"Max. Flux Conc. Channels (m3/s/m3/s)......................=");
	fprintf(Summ_file_fptr,"\t%g \n", amaxFluxCoutCh);

	fprintf(Summ_file_fptr,
		"Max. Suspended Sediment in Overland (mm)..................=");
	fprintf(Summ_file_fptr,"\t%g \n", amaxSusOv*1000/(w*w));

	fprintf(Summ_file_fptr,
		"Max. Suspended Sediment in Channels (mm)..................=");
	fprintf(Summ_file_fptr,"\t%g \n", amaxSusCh*1000/(w*w));

	fprintf(Summ_file_fptr,
		"Max. Concentration on Overland (m3/m3)....................=");
	fprintf(Summ_file_fptr,"\t%g \n", amaxSusCov);

	fprintf(Summ_file_fptr,
		"Max. Concentration in Channels (m3/m3)....................=");
	fprintf(Summ_file_fptr,"\t%g \n", amaxSusCch);

	fprintf(Summ_file_fptr,
		"Total Net Volume (mm) at the End of the Simulation: \n");

	fprintf(Summ_file_fptr,
		"    Minimum vValue ........................................=");
	fprintf(Summ_file_fptr,"%15.3f \n", totnetv_stats.min );

	fprintf(Summ_file_fptr,
		"    Maximum Value ........................................=");
	fprintf(Summ_file_fptr,"%15.3f \n",totnetv_stats.max );

	fprintf(Summ_file_fptr,
		"    Mean .................................................=");
	fprintf(Summ_file_fptr,"%15.3f \n",totnetv_stats.mean );

	fprintf(Summ_file_fptr,
		"    Standard Deviation ...................................=");
	fprintf(Summ_file_fptr,"%15.3f \n",totnetv_stats.stdev );

}