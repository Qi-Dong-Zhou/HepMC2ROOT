#####################################################################
#------------------------------------------------
#
# Configuration for each architecture
#

MAKEARCH        :=      $(shell find $(ROOTSYS)/test -name Makefile.arch)
ifeq ($(MAKEARCH), )
# 41594 or later
MAKEARCH        :=      $(shell find $(ROOTSYS)/etc -name Makefile.arch)
endif

include $(MAKEARCH)

#-----------------------------------------


SYSTEM=$(shell uname)
SYSTEM2=$(shell uname -m)
m32=$(shell if [ "$(SYSTEM2)" = "i686" ]; then echo "-m32"; fi)

CFLAGS     += $(m32) -ggdb3 -pipe -Wall
CXXFLAGS   += $(m32) -ggdb3 -pipe -Wall
CXXFLAGS  += -fPIC -pthread -Wpacked  -mpreferred-stack-boundary=8 

ROOTCFLAGS   += $(shell root-config --cflags)
ROOTLIBS     += $(shell root-config --libs) -lEG


LIB_DIR = ./eventClass/

DICTNAME     = libEvent.so
DICT_INC     = $(LIB_DIR)/include/
DICT_SRC     = $(LIB_DIR)/src/
DICT_LIB     = $(LIB_DIR)/lib/

EVENTLIBS    = $(DICT_LIB)/$(DICTNAME)

#
#-----------------------------------------
# 
# For this codes
#
#
HEPCFLAGS    = -I$(HEP_ROOT)/include
HEPLIBS      = -L$(HEP_ROOT)/lib -lHepMC -lHepMCfio
BOOSTLIBS    = -L$(BOOSTSYS)/stage/lib -lboost_iostreams -lboost_system

CFLAGS       = $(ROOTCFLAGS) $(HEPCFLAGS)
LIBS         = $(ROOTLIBS) $(HEPLIBS) $(BOOSTLIBS) 
#

INCALL += -I$(DICT_INC) 
INCALL += -I./include/ 
INCALL += -I$(HEP_ROOT)/include/ 
CXXFLAGS +=  $(INCALL) -g -lMinuit2 -fopenmp

BINDIR=./bin

TARGETS  = HepMC2ROOT 

all: $(TARGETS)	
 

HepMC2ROOT : src/HepMC2ROOT.o 
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/$@ $^ \
	$(LIBS) $(ROOTLIBS) $(ROOTGLIBS) $(EVENTLIBS) 

sample : src/sample.o src/Plots.cpp
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/$@ $^ \
	$(LIBS) $(ROOTLIBS) $(ROOTGLIBS) $(EVENTLIBS) 
 
%.o	:   %.cpp %.h
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

src/%.o  :  src/%.cpp  src/%.h
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

src/%.o  :  src/%.cpp
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

$(SRC_DIR)/%.o  :  $(SRC_DIR)/%.cpp  $(INC_DIR)/%.h
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

clean:
	rm -f *.o */*.o */*~ *~ \#*


