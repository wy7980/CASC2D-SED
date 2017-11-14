										/**************************/ 
										/*      INCLUDE FILES     */ 
										/**************************/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <time.h>
#include <malloc.h>


									/**********************************/ 
									/*			FUNCTION PROTOTYPES				*/ 
									/**********************************/ 

extern void ReadProjectFile(char ProjectName[80]);

extern void ReadGridHeaders();

extern void GridsMemAlloc();

int** intMemAlloc2d(int NoRows, int NoCols);

float** floatMemAlloc2d(int NoRows, int NoCols);

float** floatMemAlloc3d(int layer, int NoRows, int NoCols);

extern void	ReadControlFile();

extern void ReadChannFile();

extern void ReadInputGrids();

extern void InitializeVars();

extern void ChannToplg();

extern void CompInitialVol();

extern void OvrlDepth( );

extern void intercept(int j, int k);

extern void rain(int j,int k);

extern void infilt(int j, int k);

extern void Settling();

extern void OvrlRout();

extern void ovrl( int j,int k, int jj, int kk);

extern void RoutSedOvrl(float dqq, float sf,int j,int k,
																									int jj,int kk);

extern void ChannDepth();

extern float newChnDepth(float wch,float dch,float sfactor,
												 int j, int k,float addedVolume);

extern void ChannRout();

extern void chnchn(int ic,int l);

float chnDischarge(float hchan,float hh,float wch,float dch,
				float stordep,float rmanch,float a,float sf,float sfactor);

extern void RoutSedChn(float dq,float sf,int jfrom,int kfrom,
											 int jto,int kto,float wch,float hchan);

extern float KRcap(float KRcoeff,float discharge,float width,
									 float sf, int jfrom, int kfrom);

extern float EHcap(int SizeFr,float width,float depth,
											 float sf,float discharge);

extern void TransferSed(int SizeFr,float **Source[], 
												float VolToTransfer,
												int jfrom,int kfrom,int jto,int kto);

extern void findMFAC(int jfrom,int kfrom,float totQSout, 
												float discharge,float qs[4]);

extern void RoutOutlet();

extern void RoutSedOut();

extern void WriteOutflow();

extern void SedStats();

extern void WriteGrids();

extern void write2dTS(char *name, char *write_name,FILE *write_name_fptr, 
								float **ParamValue, float UnitsConv);

extern void write3dTS(char *name, char *write_name,FILE *write_name_fptr, 
								int layer, float **ParamValue[]);

extern void Reset();

extern void CompFinalVol();

extern void	SedVolumes();

extern void WriteSummFlow();

extern void WriteSummSed();

extern void GridsMemFree();

void fMemFree2d(float** matrix2d, int NoRows, int NoCols);

void iMemFree2d(int** matrix2d, int NoRows, int NoCols);

extern void	RunTime(clock_t finish);

extern double MAX(double one,double theOther);

extern double MIN(double one,double theOther);

extern struct gstats gridstats(float **inputgrid);

									/**********************************/ 
									/*				GLOBAL CONSTANTS				*/ 
									/**********************************/ 

#define g 9.81			/* Gravitational acceleration [m2/s]					*/ 
#define ROs 2.65		/* Mass density of solid particles [tons/m3]	*/ 
#define KRov 58390	/* Kilinc Constant in the overland transp.eq.	*/ 
#define KRch 58390	/* Kilinc Constant in the channel transp.eq.	*/ 
#define G 2.65			/* Specific gravity [adimensional]						*/ 



									/**********************************/ 
									/*				GLOBAL VARIABLES				*/ 
									/**********************************/ 

extern char  
			project_file[80],control_file[80],	rain_file[80],chn_file[80],
			header[300],elev_file[80],shap_file[80],soil_file[80],
			iman_file[80],sdep_file[80],node_file[80],link_file[80],
			Summ_file[80],dis_out_file[80],sed_out_file[80],
			rname[80],write_rname[80],vinfname[80],write_vinfname[80],
			dname[80],cname[80],susname[80],erosdepname[80],
			sandfluxname[80],siltfluxname[80],clayfluxname[80],
			totalfluxname[80],sandMFACname[80],siltMFACname[80],
			clayMFACname[80],totalMFACname[80];

extern int		
  		m,n,jout,kout,ncells,nman,nsoil,
			indexsdep,indexinf,indexeros,chancheck,
			nchan_link,nchan_node[100],	maxlink,ichn[50][100][3],
			iter,niter,nitrn,nprn,nplt,irain,nrg,nread,
			ifcount,icount,ipcount,
			indexdis,ndis,**iq,unitsQ,indexsed,nsed,**ised,unitsQs,
			nodatavalue, **link,**node,**isoil, **iman, **ishp;

extern float	
			w,dt,sout,wchout,dchout,sfactorout,rmanout,sovout,
			raincount,crain,*xrg,*yrg,*areaQ, *areaQs, 
			xllcorner, yllcorner,*pman, *cfactor, *pfactor, *retention,
			elconv,**e,**ret,**sdep,**vinf,**pinf,vin,vout,vinftot,
			init_ov_vol,init_ch_vol,final_ch_vol,final_ov_vol,
			chp[50][100][7],**h,**hch,*rrg,**wrint,**rtot,
			**dqov,**dqch,qout,qoutov,qpeak,tpeak,*q,
			*qsed,**qss, **qovs[4],**vols[4],**ssoil[4],**SedFluxOut[4], 
			**MFAC[4],**MaxFluxCout,**totnetv,**totsus,**SusC,
			tot_eroded[4],sus_ov[4],dep_ov[4],tot_ov[4],
			sus_ch[4],dep_ch[4],tot_ch[4],sed_out[4];

extern double 
			amaxdepth,amindepth,amaxcdepth,amincdepth, amaxvinf,aminvinf,
			amaxnetv,aminnetv,amaxFluxCoutOv,amaxFluxCoutCh,amaxrain,
			aminrain,amaxSusCh,amaxSusOv, amaxSusCch, amaxSusCov,
			ds[4],ws[4],elapsedTime;	

struct gstats {
		double min;
		double max;
		float mean;
		float stdev;};

clock_t startTime;

extern FILE *project_file_fptr;
extern FILE *shap_file_fptr;
extern FILE *sdep_file_fptr;
extern FILE *elev_file_fptr;
extern FILE *rain_file_fptr;
extern FILE *soil_file_fptr;
extern FILE *control_file_fptr;
extern FILE *chn_file_fptr;
extern FILE *node_file_fptr;
extern FILE *link_file_fptr;
extern FILE *Summ_file_fptr;
extern FILE *iman_file_fptr;
extern FILE *dis_out_file_fptr;
extern FILE *sed_out_file_fptr; 
extern FILE *debug;
