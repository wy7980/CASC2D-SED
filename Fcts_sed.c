

						/*******************************/
						/*         Fcts_sed.c          */
						/*******************************/


#include "all.h"


			/**********************************/
			/*           FUNCT: EHcap         */
			/**********************************/


/* Determines the sediment transport capacity based on the 				*/
/* Engelund and Hansen transport equation. Result is in m3				*/

extern float EHcap(int SizeFr,float width,float depth,
											 float sf,float discharge)
{
	float Cw[4], Rh,V, EHcapacity;

	/* Hydraulic radius                                             */
	Rh = (width*depth)/(width + 2 * depth);

	/* Flow velocity                                                */
	V = (float)(discharge/(width*depth));

	/* Concentration by weight by size fraction                     */
	Cw[SizeFr] = (float)(0.05*(G/(G-1)) *
							fabs(V*sf)/sqrt((G-1)*g*ds[SizeFr]) *
							sqrt(Rh*fabs(sf)/((G-1)*ds[SizeFr]) ) ) ;

	/* Engelund and Hansen transport capacity  (in m3)              */
	EHcapacity = (float)(discharge * Cw[SizeFr] / 2.65)*dt ;

	return(EHcapacity);

}
			/**********************************/
			/*          FUNCT: KRcap          */
			/**********************************/


/* Determines the sediment transport capacity based on the 				*/
/* Kilinc and Richardson transport equation. Result is in m3			*/

extern float KRcap(float KRcoeff,float discharge,float width,
									 float sf, int jfrom, int kfrom)
{
	int SoilType;
	float KRcapacity, UnitDischarge,Cusle,Kusle,Pusle;

	UnitDischarge = (float)(fabs(discharge/width));

	SoilType = isoil[jfrom][kfrom];

	Cusle = cfactor[iman[jfrom][kfrom]];
	Kusle = pinf[SoilType][7];
	Pusle = pfactor[iman[jfrom][kfrom]];

	KRcapacity = (float)(KRcoeff * pow(fabs(sf),1.66) *
							pow(UnitDischarge,2.035) * Cusle * Kusle * Pusle
							* width * dt);

	return(KRcapacity);

}

			/**********************************/
			/*        FUNCT: TransferSed      */
			/**********************************/

/* Transfers a certain volume of sediment, VolToTransfer, from		*/
/* an outgoing cell (jfrom,kfrom) to receiving cell (jto,kto).The */
/* source, can be the suspended,deposited or parent material in		*/
/* outgoing cell.  The transferred volume of sed. will be added		*/
/* in all cases onto the suspended portion of the receiving cell. */
/* If the outgoing cell is the outlet cell, the VolToTransfer is	*/
/* not added into a receiving cell but to the variable that holds */
/* the total volume of sediment leaving the basin by size fraction*/

extern void TransferSed(int SizeFr,float **Source[],
												float VolToTransfer,
												int jfrom,int kfrom,int jto,int kto)
{
	/* For each size fraction, substracts the sediment volume that  */
  /* has been transported from the suspended, deposited or parent */
	/* material of the outgoing cell                                */
	Source[SizeFr][jfrom][kfrom] -= VolToTransfer;


	if(jfrom==jout && kfrom==kout)
	{
		/* If outgoing cell is the outlet cell, keeps track by size   */
		/* fraction of the volume of sediment that left the basin     */
		sed_out[SizeFr] += VolToTransfer;
	}
	else
	{
		/* if outgoing cell is not the outlet cell, it adds by size   */
		/* fraction the transported sediment to the suspended portion */
		/* of the receiving cell                                      */
		qovs[SizeFr][jto][kto] += VolToTransfer;
	}
}

			/**********************************/
			/*        FUNCT: FindMFAC         */
			/**********************************/

/* For each time step, finds the maximum flux-averaged concentr.  */
/* leaving the outgoing cell for the total volume of sediment     */
/* (** MaxFluxCout) or by size fraction (** MFAC[SizeFr])         */

extern void findMFAC(int jfrom,int kfrom,float totQSout,
												float discharge,float qs[4])
{
	int SizeFr;

	if(MaxFluxCout[jfrom][kfrom] < totQSout/dt/fabs(discharge)
		        &&   fabs(discharge) > 1E-4)
	{
	  /* For the total volume of sediment leaving the outgoing cell */
		MaxFluxCout[jfrom][kfrom] =
															(float)(totQSout/dt/fabs(discharge));

		/* By size fraction                                           */
		for (SizeFr = 1; SizeFr <=3; SizeFr++)
		{
			MFAC[SizeFr][jfrom][kfrom] =
				                    (float)(qs[SizeFr]/dt/fabs(discharge));
		}
	}
}
