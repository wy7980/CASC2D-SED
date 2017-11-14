						/*******************************/
						/*         RoutSedOvrl.c       */
						/*******************************/


#include "all.h"

extern void RoutSedOvrl(float dqq, float sf,int jfrom,int kfrom,
																									int jto,int kto)
{
	float V, qsSUS[4],qsADV[4],qsSUStot,SUStot, DEPtot,qsBM[4],
				totXSScap,capacity[4],RESIDcap, qsBMtot,
				qsEROS[4],qsEROStot,percent[4],qs[4],qsKR;

	int SizeFr,SoilType;

	/* SizeFr: Soil size fraction:    1: sand; 2: silt; 3: clay     */
	/* Outgoing cell : (jfrom, kfrom)                               */
	/* Receiving cell: (jto, kto)                                   */

	/* Flow velocity [m/s]                                          */
	V = (float)(fabs(dqq)/(w * h[jfrom][kfrom]));

	/* Initialize sediment volumes to zero                          */
	qsSUStot = 0;     /* Total transported suspended volume         */
	qsBMtot = 0;      /* Total transported bed material volume      */
	qsEROStot = 0;    /* Total transported eroded material volume   */
	SUStot = 0;       /* Total susp. volume in outgoing cell        */
	DEPtot = 0;       /* Total deposited volume in outgoing cell    */

	/* Finds soil type for the outgoing overland cell               */
	SoilType = isoil[jfrom][kfrom];

	/* Transport Capacity using the Kilinc-Richardson equation      */
	qsKR = KRcap(KRov,dqq,w,sf,jfrom,kfrom);

	/* Initialize transport volumes by size fraction to zero        */
	for(SizeFr=1;SizeFr<=3;SizeFr++)
	{                     /* For size fraction SizeFr:              */
		qsSUS[SizeFr] = 0;  /* transported volume from suspension     */
		qsBM[SizeFr] = 0 ;  /* transported volume from deposition     */
		qsEROS[SizeFr] = 0; /* transported volume from parent material*/
		qs[SizeFr] = 0;     /* total transported volume               */
		/* Outgoing cell total suspended and deposited sediment       */
		SUStot += qovs[SizeFr][jfrom][kfrom];
		DEPtot += vols[SizeFr][jfrom][kfrom];

	}

	for(SizeFr=1;SizeFr<=3;SizeFr++) /* For each size fraction      */
	{
		/* Is this size fraction present in suspended portion ?       */
		if(qovs[SizeFr][jfrom][kfrom] > 0)
		{
			if(qsKR < SUStot) /* Transport capacity is < total suspended*/
			{
				/* Volume that can be transported using the KR equation   */
				capacity[SizeFr] = qsKR * qovs[SizeFr][jfrom][kfrom]/SUStot;
				/* Volume that can be transported by advective processes  */
				qsADV[SizeFr] = qovs[SizeFr][jfrom][kfrom] * V * dt / w;
				/* Transport the maximum between the last two quantities  */
				qsSUS[SizeFr] = (float)(MAX(capacity[SizeFr],qsADV[SizeFr]));
			}
			else /* If transport capacity is > total suspended sediment */
			{
				/* Transport all the suspended sediment for this size fr. */
				qsSUS[SizeFr] = qovs[SizeFr][jfrom][kfrom];
			}

			/* Transfers the volume qsSUS[SizeFr] of sediment size      */
			/* fraction, SizeFr, in suspension in the outgoing cell     */
			/* to the suspended portion of the receiving cell           */
			TransferSed(SizeFr,qovs,qsSUS[SizeFr],jfrom,kfrom,jto,kto);

			/* Keeps track of the total volume of sediment coming from  */
			/* the suspended material portion of the outgoing cell      */
			qsSUStot += qsSUS[SizeFr];
		}
	}

	/* Reduces the transport capacity by the volume that has already*/
	/* been transported from the outgoing cell to get the total     */
	/* excess capacity                                              */
	totXSScap = (float)(MAX(0,qsKR - qsSUStot));

	/* If there is an excess transport capacity, and provided that  */
	/* the outgoing cell has previously deposited material, we use  */
	/* this capacity to put this sediment in suspension and move it */
	/* to the suspended portion of the receiving cell               */
	if(totXSScap > 0 && DEPtot > 0)
	{
		for(SizeFr=1;SizeFr<=3;SizeFr++)
		{
		/* Is this size fraction present in deposited portion ?       */
			if(vols[SizeFr][jfrom][kfrom] > 0)
			{
				/* Excess transport capacity is < total deposited sediment*/
				if(totXSScap < DEPtot)
				{

					/* Volume that can be transported for this size         */
					/* fraction is proportional to its percentage in the    */
					/* total deposited sediment                             */
					qsBM[SizeFr] =
										totXSScap * vols[SizeFr][jfrom][kfrom] / DEPtot;
				}
				else /* If transport capacity is > total deposited sed.   */
				{
					/* Transport all the deposited sed. for this size fr.   */
					qsBM[SizeFr] = vols[SizeFr][jfrom][kfrom];
				}

			/* Transfers the volume qsBM[SizeFr] of sediment size       */
			/* fraction, SizeFr, in deposition in the outgoing cell     */
			/* to the suspended portion of the receiving cell           */
				TransferSed(SizeFr,vols,qsBM[SizeFr],jfrom,kfrom,jto,kto);

			/* Keeps track of the total volume of sediment leaving      */
			/* the deposited material portion of the outgoing cell      */
		  qsBMtot += qsBM[SizeFr];
			}
		}
	}

	/* Reduces the excess transport capacity by the total volume    */
	/* of sediment, qsBMtot,that has alrady been transported        */
	/* from the deposited portion of the outgoing cell              */
	RESIDcap = (float)(MAX(0,totXSScap - qsBMtot));

	/* Any residual transport capacity is used to erode the parent  */
	/* material.  Erosion by size fraction is proportional to its   */
	/* percentage in the parent material                            */
	if(RESIDcap >0)
	{
		for(SizeFr=1;SizeFr<=3;SizeFr++)
		{
			/* Percentage of fraction, SizeFr, in the parent material   */
			percent[SizeFr] = pinf[SoilType][SizeFr + 3];

			/* Volume of eroded parent material corresponding to size   */
			/* fraction SizeFr                                          */
			qsEROS[SizeFr] = RESIDcap * percent[SizeFr];

			/* Keeps track of the total volume of sediment coming from  */
			/* the parent material portion of the outgoing cell         */
			qsEROStot += qsEROS[SizeFr];

			/* Transfers the volume qsEROS[SizeFr] of sediment size     */
			/* fraction, SizeFr from the outgoing cell parent material  */
			/* to the suspended portion of the receiving cell           */
			TransferSed(SizeFr,ssoil,qsEROS[SizeFr],jfrom,kfrom,jto,kto);
		}
	}

	/* Keeps track of the total sediment volume leaving the         */
	/* outgoing cell (coming from all 3 sources)                    */
	qss[jfrom][kfrom] += qsSUStot + qsBMtot + qsEROStot;

	for(SizeFr=1;SizeFr<=3;SizeFr++)
	{
		/* Total sediment volume leaving the outgoing cell by size    */
		/* fraction                                                   */
		qs[SizeFr] = qsSUS[SizeFr] + qsBM[SizeFr] + qsEROS[SizeFr];

		/* Keeps track of the sediment flux [m3/s] by size fraction   */
		/* out of the outgoing cell                                   */
		SedFluxOut[SizeFr][jfrom][kfrom] += qs[SizeFr] / dt;
	}

	/* Calls the function findMFAC to find the maximum flux         */
	/* averaged concentration out of the outgoing cell              */
	findMFAC(jfrom,kfrom,qsKR,dqq,qs);

}