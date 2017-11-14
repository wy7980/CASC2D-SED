						/*******************************/
						/*         RoutSedOut.c        */
						/*******************************/


#include "all.h"

extern void RoutSedOut()

{
	if(ishp[jout][kout] == 2 )  /* Case of a channel cell           */
	{
		if(hch[jout][kout] != 0)
		{
			RoutSedChn(qout,sout,jout,kout,1,1,wchout,hch[jout][kout]);
		}
	}

	else /* case of an overland cell                                */
	{
		if(h[jout][kout] != 0)
		{
			RoutSedOvrl(qoutov,sovout,jout,kout,1,1);
		}
	}
}