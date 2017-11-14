						/*******************************/ 
						/*           infilt.c          */ 
						/*******************************/ 


#include "all.h"

extern void infilt(int j, int k)
{

	int iinf;

	float hydcon, cs, smd, p1, p2, rinf;

	iinf = isoil[j][k];
	hydcon = pinf[iinf][1];
	cs = pinf[iinf][2];
	smd = pinf[iinf][3];

	/* Infiltration rate																						*/ 
	
	p1 = (float)(hydcon*dt - 2.0*vinf[j][k]);
	p2 = hydcon*(vinf[j][k] + cs*smd);
	rinf = (float)((p1 + sqrt(pow(p1,2.0) + 8.0*p2*dt))/(2.0*dt));

	/* When the Rate of Infiltration is Greater Than HOV/DT,				*/	
	/* then all the water on the overland cell is assumed to				*/	
	/* be	infiltrated and the overland depth is reduced to zero.		*/	

	if (h[j][k]/dt <= rinf) 
	{
		rinf = h[j][k]/dt;
		h[j][k] = 0.0;
	}
	else
	{
		h[j][k] = h[j][k] - rinf*dt;
	}

	/* Accumulated volume of infiltrated water											*/ 

	vinf[j][k] = vinf[j][k] + rinf*dt;
}
