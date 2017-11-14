
#include "all.h"

			/**********************************/ 
			/*  GLOBAL VARIABLES DECLARATION  */ 
			/**********************************/ 

char  project_file[80],control_file[80],	rain_file[80],chn_file[80],
			header[300],elev_file[80],shap_file[80],soil_file[80],
			iman_file[80],sdep_file[80],node_file[80],link_file[80],
			Summ_file[80],dis_out_file[80],sed_out_file[80],
			rname[80],write_rname[80],vinfname[80],write_vinfname[80],
			dname[80],cname[80],susname[80],erosdepname[80],
			sandfluxname[80],siltfluxname[80],clayfluxname[80],
			totalfluxname[80],sandMFACname[80],siltMFACname[80],
			clayMFACname[80],totalMFACname[80];
			

int		m,n,jout,kout,ncells,nman,nsoil,
			indexsdep,indexinf,indexeros,chancheck,
			nchan_link,nchan_node[100],	maxlink,ichn[50][100][3],
			iter,niter,nitrn,nprn,nplt,irain,nrg,nread,
			ifcount,icount,ipcount,
			indexdis,ndis,**iq,unitsQ,indexsed,nsed,**ised,unitsQs,
			nodatavalue, **link,**node,**isoil, **iman, **ishp;

float	w,dt,sout,wchout,dchout,sfactorout,rmanout,sovout,
			raincount,crain,*xrg,*yrg,*areaQ, *areaQs,
			xllcorner, yllcorner,*pman, *cfactor, *pfactor, *retention,
			elconv,**e,**ret,**sdep,**vinf,**pinf,vin,vout,vinftot,
			init_ov_vol,init_ch_vol,final_ch_vol,final_ov_vol,
			chp[50][100][7],**h,**hch,*rrg,**wrint,**rtot,
			**dqov,**dqch,qout,qoutov,qpeak,tpeak,*q,
			*qsed,**qss, **qovs[4],**vols[4],**ssoil[4],**SedFluxOut[4],
			**MFAC[4],**MaxFluxCout,**totnetv,**totsus, **SusC,
			tot_eroded[4],sus_ov[4],dep_ov[4],tot_ov[4],
			sus_ch[4],dep_ch[4],tot_ch[4],sed_out[4];

double amaxdepth,amindepth,amaxcdepth,amincdepth, amaxvinf,aminvinf,
			amaxnetv,aminnetv,amaxFluxCoutOv,amaxFluxCoutCh,amaxrain,
			aminrain,amaxSusCh,amaxSusOv, amaxSusCch, amaxSusCov,
			ds[4],ws[4],elapsedTime;

clock_t startTime;

FILE *project_file_fptr = NULL;
FILE *shap_file_fptr = NULL;
FILE *sdep_file_fptr = NULL;
FILE *elev_file_fptr = NULL;
FILE *rain_file_fptr = NULL;
FILE *soil_file_fptr = NULL;
FILE *control_file_fptr = NULL;
FILE *chn_file_fptr = NULL;
FILE *node_file_fptr = NULL;
FILE *link_file_fptr = NULL;
FILE *Summ_file_fptr = NULL;
FILE *iman_file_fptr = NULL;
FILE *dis_out_file_fptr = NULL;
FILE *sed_out_file_fptr = NULL;
FILE *debug = NULL;


			/*******************************/ 
			/*   CASC2D_SED MAIN PROGRAM   */ 
			/*******************************/ 

int main(argc,argv)
	int argc;
	char *argv[];
	{
				/*********************************************/ 
				/*         Read and initialize data          */ 
				/*********************************************/ 

		/* Time CASC2D running time																		*/ 
		startTime = clock();

		/* Reads the project files names															*/ 
		ReadProjectFile(argv[1]);
 
		/* Reading in the CONTROL Information													*/ 
		ReadControlFile();

		/* Reads the input grids headers															*/ 
		ReadGridHeaders();
 
		/* Dynamically allocates memory to the input & output grids		*/ 
		GridsMemAlloc();

		/* Reading Input Grids																				*/ 
		ReadInputGrids();
 
		/* Initializing Variables																			*/ 
		InitializeVars();

		/* Determines channel network topology and variables					*/ 
		if(chancheck == 1) 
		{
			ReadChannFile();
			ChannToplg();
		}

		/* Computing Initial Storage Volume for Overland and Channels	*/ 
		if(indexsdep == 1) CompInitialVol();

				/*********************************************/ 
				/*            Event time loop                */ 
				/*********************************************/ 

		for(iter=1;iter<=niter;iter++)
		{

			/* Updating overland and channels water depth								*/ 
			OvrlDepth( );
			if(chancheck == 1)ChannDepth();

			/* Overland and channel flow routing												*/ 
			OvrlRout();
			if(chancheck == 1) ChannRout();

			/* Flow routing at the outlet																*/ 
			RoutOutlet();

			/* Sediment settling for this water depth and time dt				*/	
			if (indexeros == 1)	Settling();

			/* Sediment routing at the outlet, total erosion/deposition	*/ 
			/* volumes, sediment max./min values	and paticle settling 	*/ 
			if (indexeros == 1)
			{
				if(qout != 0) RoutSedOut();
				SedStats();
			}

			/* Write outflow to screen and files												*/ 
			WriteOutflow();

			/* Write output grids																				*/ 
			WriteGrids();

			/* Reset grids to zero																			*/ 
			Reset();

		} /* End of Time Loop */ 

				/*********************************************/ 
				/* Computes final volumes & writes results   */ 
				/*********************************************/ 

		/* Compute final water volumes on the overland and channels		*/ 
		CompFinalVol();

		/* Writing summary file																				*/ 
		WriteSummFlow();

		/* Compute final sed. volumes on the overland and channels		*/ 
		if(indexeros == 1)
		{
			SedVolumes();
			WriteSummSed();
		}

		/* Deallocate memory */ 
		GridsMemFree();

		/* Computes casc2d running time																*/ 
		RunTime(clock());

	} /* End of Main Program */ 
