PROGRAM=transpose

include ../../common/Cxx11.defs
include ../../common/PRKVERSION

CXXFLAGS  = $(DEFAULT_OPT_FLAGS)
CXXFLAGS += -DPRKVERSION=$(CPRKVERSION)
CXXFLAGS += -DRADIUS=$(RADIUS) $(STARFLAG)
CXXFLAGS += -I..

.PHONY: all clean run

all: $(PROGRAM)

$(PROGRAM): $(PROGRAM).cc
	$(CXX) $(CXXFLAGS) $< -o $@

run: $(PROGRAM)
	$(PROGRAM) 10 4000 32

clean:
	-rm -f *.o
	-rm -f *.optrpt
	-rm -f *.dwarf
	-rm -rf *.dSYM
	-rm -f $(PROGRAM)

