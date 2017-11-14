						/*******************************/ 
						/*          RunTime.c          */ 
						/*******************************/ 


#include "all.h"

extern void	RunTime(clock_t finish)
{
	double elapsedTime;

	fprintf(Summ_file_fptr,
		"\nProgram stops at simulation minute:%10.2f\n",(iter-1)*dt/60);

	elapsedTime = (double)(finish - startTime)/CLOCKS_PER_SEC;
	
	fprintf(Summ_file_fptr, 
		"\nCASC2D RUNNING TIME:%10.2f minutes\n", elapsedTime/60);

	fclose(Summ_file_fptr);
}