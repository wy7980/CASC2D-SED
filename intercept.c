						/*******************************/ 
						/*         intercept.c         */ 
						/*******************************/ 


#include "all.h"

extern void intercept(int j, int k)
{

	if (wrint[j][k] * dt >= ret[j][k])
	{
		wrint[j][k] = wrint[j][k] - ret[j][k] / dt;
		ret[j][k] = 0;
	}
	else
	{
		ret[j][k] = ret[j][k] - wrint[j][k] * dt;
		wrint[j][k] = 0;
	}

}