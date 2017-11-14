						/*******************************/ 
						/*       WriteOutflows.c       */ 
						/*******************************/ 


#include "all.h"

extern void WriteOutflow()
{
	int ill,ils,jsed,ksed,i;

	/******************************/ 
	/*   write results to screen  */ 
	/******************************/ 
	if(chancheck == 1)
	{
		printf(
		"Time (Min) = %7.2f\tQ (m3/s)= %7.2f\tChan. Depth(m) = %7.3f \n"
													,iter*dt/60.0, qout,hch[jout][kout]);
	}
	else
	{
		printf(
		"Time (Min) = %7.2f\tQ (m3/s) = %7.2f\tOver. Depth(m) = %7.3f\n"
														 ,iter*dt/60.0,qout,h[jout][kout]);
	}

	/******************************************************/ 
	/*   write outflow and sediment flow to output files	*/ 
	/******************************************************/ 

	if(iter==1) 
	{
		fprintf(dis_out_file_fptr," Time_(min) ");
		if(indexeros == 1)fprintf(sed_out_file_fptr,"Time_(min) ");
		for (i=1;i<=ndis;i++)
		{
			fprintf(dis_out_file_fptr,"Row%iCol%i ",iq[i][1],iq[i][2]);
			if(indexeros == 1)
					fprintf(sed_out_file_fptr,"Row%iCol%i ",
																					ised[i][1],ised[i][2]);
		}
		fprintf(dis_out_file_fptr,"\n");
		if(indexeros == 1)fprintf(sed_out_file_fptr,"\n");
	}

	if(icount == nprn)
	{
		/* Write outflow discharge at selected locations							*/ 



		fprintf(dis_out_file_fptr,"%.2f",iter*dt/60.0);

		for(ill=1; ill<=ndis; ill++)
		{
		  switch(unitsQ)
			{ 
	 			case 1: /* Discharge in m3/s */ 
	 				fprintf(dis_out_file_fptr,"%15.3f ",q[ill]);
	 				break;

	 			case 2: /* Discharge in cfs */ 
	 				fprintf(dis_out_file_fptr,"%15.3f ",
	 														q[ill]* pow(3.28084,3));
	 				break;

	 			case 3: /* Discharge in mm/h */ 
	 				fprintf(dis_out_file_fptr,"%15.3f ",
	 													q[ill] / areaQ[ill] * 360);
	 				break;
			}
		}

		fprintf(dis_out_file_fptr,"\n");

		/* Writing outflow sediment Data at selected locations			*/ 
		
		if(indexeros == 1 && sed_out_file[0] != '\0')
		{

			fprintf(sed_out_file_fptr,"%.2f",iter*dt/60.0);

			for(ils=1; ils<=nsed; ils++)
			{
	 			jsed = ised[ils][1];
	 			ksed = ised[ils][2];

	 			qsed[ils] = qss[jsed][ksed]/dt;

	 			switch(unitsQs)
	 			{
					case 1: /* Sediment discharge in m3/s */ 
						fprintf(sed_out_file_fptr,"%15.5f ", qsed[ils]);
						break;
					case 2: /* Sediment discharge in tons/ha/day */ 
						fprintf(sed_out_file_fptr,"%15.5f ",
	 									 qsed[ils] / areaQs[ils] * ROs * 86400);
						break;
	 			}
			}
			fprintf(sed_out_file_fptr,"\n");
			
			fprintf(debug,"%.2f \t %g \t %g \t %g \n",iter*dt/60,
				SedFluxOut[1][jout][kout],SedFluxOut[2][jout][kout],
				SedFluxOut[3][jout][kout]);
		}
						
			icount = 1;
	}

	else
	{
		icount = icount + 1;
	}

}