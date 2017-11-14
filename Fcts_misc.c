						/*******************************/ 
						/*         Fcts_misc.c        */ 
						/*******************************/ 

#include "all.h"

			/**********************************/ 
			/*               FUNCT: max       */ 
			/**********************************/ 

/* Finds the maximum between two floating numbers */ 

extern double MAX(double one,double theOther)

{
	double maximum;

	if (one >= theOther)
		maximum = one;
	else
		maximum = theOther;

	return(maximum);
}

			/**********************************/ 
			/*               FUNCT: min       */ 
			/**********************************/ 

/* Finds the minimum between two floating numbers */ 

extern double MIN(double one,double theOther)

{
	double minimum;

	if (one <= theOther)
		minimum = one;
	else
		minimum = theOther;

	return(minimum);
}
