include ../common/FORTRAN.defs

ifndef RADIUS
  RADIUS=2
endif

STARFLAG   = -DSTAR

FCFLAGS  = $(DEFAULT_OPT_FLAGS)
FCFLAGS += -DRADIUS=$(RADIUS) $(STARFLAG)

.PHONY: all clean serial pretty openmp coarray

all: serial pretty openmp coarray target

serial: p2p stencil transpose

pretty: stencil-pretty transpose-pretty

openmp: p2p-openmp-tasks p2p-openmp-doacross p2p-openmp-datapar stencil-openmp transpose-openmp

coarray: p2p-coarray stencil-coarray transpose-coarray

target: p2p-openmp-target stencil-openmp-target transpose-openmp-target

ornlacc: p2p-ornlacc stencil-ornlacc transpose-ornlacc

%: %.f90
	$(FC) $(FCFLAGS) $< -o $@

%-pretty: %-pretty.f90
	$(FC) $(FCFLAGS) $< -o $@

p2p-openmp-tasks: p2p-openmp-tasks.f90
	$(FC) $(FCFLAGS) $(OPENMPFLAG) $< -o $@

p2p-openmp-doacross: p2p-openmp-doacross.f90
	$(FC) $(FCFLAGS) $(OPENMPFLAG) $< -o $@

p2p-openmp-datapar: p2p-openmp-datapar.f90
	$(FC) $(FCFLAGS) $(OPENMPFLAG) $< -o $@

%-openmp: %.f90
	$(FC) $(FCFLAGS) $(OPENMPFLAG) $< -o $@

%-coarray: %-coarray.f90
	$(CAFCOMPILER) $(FCFLAGS) $< $(COARRAYFLAG) -o $@

%-target: %-target.f90
	$(FC) $(FCFLAGS) $(OPENMPFLAG) $(OFFLOADFLAG) $< -o $@

%-ornlacc: %-ornlacc.f90
	$(FC) $(FCFLAGS) $(ORNLACCFLAG) $< -o $@

clean:
	-rm -f *.o
	-rm -f *.i90
	-rm -f *__genmod.f90 # Intel Fortran
	-rm -f *__genmod.mod # Intel Fortran
	-rm -f *.optrpt
	-rm -f *.dwarf
	-rm -rf *.dSYM # Mac
	-rm -f p2p                   stencil                 transpose
	-rm -f p2p-pretty            stencil-pretty          transpose-pretty
	-rm -f p2p-coarray           stencil-coarray         transpose-coarray
	-rm -f p2p-openmp-tasks      stencil-openmp          transpose-openmp
	-rm -f p2p-openmp-doacross   p2p-openmp-datapar
	-rm -f p2p-openmp-target     stencil-openmp-target   transpose-openmp-target
	-rm -f p2p-ornlacc 	     stencil-ornlacc         transpose-ornlacc
