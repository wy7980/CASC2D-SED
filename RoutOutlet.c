						/*******************************/ 
						/*         RoutOutlet.c        */ 
						/*******************************/ 


#include "all.h"

extern void RoutOutlet()
{
	int ill;
	float hout, alfa,qoutch;

	qoutov = 0.0;
	qoutch = 0.0;

	/* FIRST:calculate the flow going out from the overl. portion		*/ 
	
	alfa = (float)(sqrt(sovout)/pman[iman[jout][kout]]);

	/* Discharge from overland flow.  NOTE: because the water from  */ 
	/* this part of the outlet overland cell was already "poured"		*/ 
	/* into the channel when updating the channel depth (channDepth)*/	
	/* qoutov = 0 when the channel routing is selected							*/ 

	if(h[jout][kout] > sdep[jout][kout]) 
	{
		qoutov = 
			(float)(w*alfa*pow((h[jout][kout]-sdep[jout][kout]),1.667));
	}

	/* Overland water depth at outlet cell is reduced after taking	*/ 
	/* the outflow out of the cell																	*/ 
	
	h[jout][kout] = (float)(h[jout][kout] - qoutov*dt/(pow(w,2.0)));

	/* SECOND:calculate the flow going out from the channel portion	*/ 

	if(chancheck == 1 && hch[jout][kout] > sdep[jout][kout])
	{
		hout = hch[jout][kout] - sdep[jout][kout];

		qoutch = chnDischarge(hch[jout][kout],hout,wchout,dchout,
					              sdep[jout][kout],rmanout,1,sout,sfactorout);

		dqch[jout][kout] = dqch[jout][kout] - qoutch;
	}

	/* The total outflow at the basin's outlet is given by adding		*/ 
	/* the outflow from the overland & channel portion of the cell	*/ 
	
	qout = qoutov + qoutch;

	/* Keeping Track of the Total Outflow Volume										*/ 
	
	vout = vout + qout*dt;

	/* Checking to see if the Peak Flow has been reached						*/ 
	
	if(qout > qpeak)
	{
	 qpeak = qout;
	 tpeak = (float)( iter*dt/60.0);
	}
	
	/* Populating the Output Flows at the Watershed Outlet					*/ 
	
	for(ill = 1;ill <= ndis; ill++)
	{
	 if(jout == iq[ill][1] && kout == iq[ill][2])
	 {
		 q[ill] = qout;
	 }
	}

}