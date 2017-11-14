						/*******************************/
						/*         RoutSedChn.c        */
						/*******************************/


#include "all.h"

			/**********************************/
			/*        FUNCT: RoutSedChn       */
			/**********************************/

extern void RoutSedChn(float dq,float sf,int jfrom,int kfrom,
											 int jto,int kto,float wch,float hchan)
{
	int SizeFr;
	float TotQs,V,supply,qs[4],adv_factor,
				EHvol[4],SUSvol[4], XSScap[4], BMvol[4];

	/* Total sediment volume out of outgoing cell is initialized   */
	TotQs = 0.0;

	/* Flow velocity (m/s)                                         */
	V = (float)(dq/(wch*hchan));


	for (SizeFr=1; SizeFr<=3;SizeFr++)
	{
	  /* Sediment supply in the outgoing cell if found in suspension*/
		/* (**qovs) and/or in deposition (**vols)                     */
	  supply = qovs[SizeFr][jfrom][kfrom] + vols[SizeFr][jfrom][kfrom];

		/* initialize qs to 0 in case that supply = 0	*/
		qs[SizeFr] = 0;

		/* If there is sediment supply in the outgoing cell           */
		if (supply != 0)
		{
			/* Transport capacity [m3] for size fraction SizeFr	using  	*/
			/* the Engelund and Hansen equation                         */
			EHvol[SizeFr] = EHcap(SizeFr,wch,hchan,sf,dq);

			/* Suspended sediment transport capacity [m3] by advection	*/
			/* Limit this transport by availability											*/

			adv_factor = (float)(MIN(V*dt/w,1));

			SUSvol[SizeFr] = qovs[SizeFr][jfrom][kfrom] * adv_factor;

			/* Transfers the volume SUSvol[SizeFr] of sediment size     */
			/* fraction, SizeFr in suspension in the outgoing cell      */
			/* to the suspended portion of the receiving cell           */

			TransferSed(SizeFr,qovs,SUSvol[SizeFr],jfrom,kfrom,jto,kto);

			/* Excess capacity [m3] to move seds. from the bed-material	*/

			XSScap[SizeFr] = (float)(MAX(0, EHvol[SizeFr] - SUSvol[SizeFr]));

			/* Bed-material transport capacity [m3] by advection				*/

			BMvol[SizeFr] = vols[SizeFr][jfrom][kfrom] * adv_factor;

			/* Volume of bed-material transported	out of (jfrom,kfrom)	*/

			BMvol[SizeFr] = (float)(MIN(XSScap[SizeFr],BMvol[SizeFr]));

			/* Transfers the volume BMvol[SizeFr] of sediment size      */
			/* fraction, SizeFr in deposition in the outgoing cell      */
			/* to the suspended portion of the receiving cell           */

			TransferSed(SizeFr,vols,BMvol[SizeFr],jfrom,kfrom,jto,kto);


			/* Total volume of transported sediment from outgoing cell	*/

			qs[SizeFr] = SUSvol[SizeFr] + BMvol[SizeFr];

			/* Updates total sediment volume leaving the outgoing cell  */

			qss[jfrom][kfrom] += qs[SizeFr];

			/* Keeps track of sediment flux out of the outgoing cell    */

			SedFluxOut[SizeFr][jfrom][kfrom] += qs[SizeFr] / dt;

			/* Total sediment volume leaving the outgoing cell      		*/

			TotQs += qs[SizeFr];
		}
	}

	/* Calls the function findMFAC to find the maximum flux         */
	/* averaged concentration out of the outgoing cell              */
	findMFAC(jfrom,kfrom,TotQs,dq,qs);

}
