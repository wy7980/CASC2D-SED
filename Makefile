CC=gcc
CFLAGS=-g
LIBS=-lm
target=main


objs = casc2d_sed.o \
	ChannDepth.o \
	ChannToplg.o \
	ChanRout.o \
	CompVolumes.o \
	Fcts_chann.o \
	Fcts_misc.o \
	Fcts_sed.o \
	Fcts_stats.o \
	infilt.o \
	InitializeVars.o \
	intercept.o \
	MemAlloc.o \
	MemFree.o \
	OvrlDepth.o \
	OvrlRout.o \
	rain.o \
	ReadChannFile.o \
	ReadControlFile.o \
	ReadGrids.o \
	ReadProjectFile.o \
	Reset.o \
	RoutOutlet.o \
	RoutSedChn.o \
	RoutSedOut.o \
	RoutSedOvrl.o \
	RunTime.o \
	SedStats.o \
	SedVolumes.o \
	Settling.o \
	WriteGrids.o \
	WriteOutflows.o \
	WriteSummFlow.o \
	WriteSummSed.o \

all:${target}

${target}: ${objs}
	${CC} -o $@ $^ ${CFLAGS} ${LIBS}	

clean:
	rm -rf *.o
	rm -rf ${target}
