CC         = clang
MAKEDEPEND = $(CC) -MM -MG
CPROTO     = cproto
GNUPLOT    = gnuplot

CPFLAGS = -q

ifeq ($(CC), clang)
  CFLAGS  = -Weverything -Wextra -pedantic $(LDFLAGS)
else
  CFLAGS  = -Wextra -pedantic -std=c99 $(LDFLAGS)
endif

LDLIBS    = $(shell gsl-config --libs)

.PHONY: clean headers

.SUFFIXES:
.SUFFIXES:  .o .h .d .c .res

%.o : %.c
	$(CC) -c $(CFLAGS) $<

%.h : %.c
	$(CPROTO) $(CPFLAGS) $< -o $@

%.d : %.c
	$(MAKEDEPEND) $< -MF $@

%.res: ising-demo-%
	./$< > $@

all: ising-demo-metropolis

OBJSM = ising-demo-metropolis.o ising.o metropolis.o matrixmem.o progressbar.o
SRCSM = $(OBJSM:.o=.c)
HDRSM = $(OBJSM:.o=.h)
DEPSM = $(OBJSM:.o=.d)

ising-demo-metropolis: headers_m $(OBJSM)
	$(CC) $(LDFLAGS) $(OBJSM) $(LDLIBS) -o $@

headers_m:
	@#$(foreach var,$(SRCSM),touch --reference=$(var) $(var:.c=.h);)
	touch -d "2000-01-01" $(HDRSM)

-include $(DEPSM)

show: metropolis.res metropolis.gp
	$(GNUPLOT) metropolis.gp
	evince metropolis.pdf >& /dev/null &

clean:
	rm -f *.*~
	rm -f ising-demo-metropolis $(OBJSM) $(HDRSM) $(DEPSM)
