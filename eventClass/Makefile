#####################################################################
#------------------------------------------------
#
# Configuration for each architecture
# (Updated for  ROOT version > 5.32)

MAKEARCH        :=      $(shell find $(ROOTSYS)/test -name Makefile.arch)
ifeq ($(MAKEARCH), )
# 41594 or later
MAKEARCH        :=      $(shell find $(ROOTSYS)/etc -name Makefile.arch)
endif

#include $(ROOTSYS)/test/Makefile.arch
include $(MAKEARCH)

# For MAC OS X users 
ifneq (,$(filter $(ARCH),macosx macosx64))
SOFLAGS  += -install_name $(LIB_DIR)/$(LIBNAME).so
endif

#-------------------------------------------------------------------

INC_DIR       = ./include
SRC_DIR       = ./src
LIB_DIR       = $(PWD)/lib
#-------------------------------------------------------------------
LIBNAME          = libEvent
# For EventBuild
LIBEVENT_HLIST  =  Event.h 
LIBEVENT_HLISTS =  $(INC_DIR)/Event.h
LIBEVENT_LIBS   =  $(SRC_DIR)/Event.o

#LIBEVENT_HLIST  +=  analysis.h
#LIBEVENT_HLISTS +=  $(INC_DIR)/analysis.h
#LIBEVENT_LIBS   +=  $(SRC_DIR)/analysis.o

LIBEVENT_LIBS   +=  $(SRC_DIR)/$(LIBNAME).o 

INCALL += -I$(INC_DIR) 
#-------------------------------------------------

HEPCFLAGS    = -I$(HEP_ROOT)/include
HEPLIBS      = -L$(HEP_ROOT)/lib -lHepMC -lHepMCfio
BOOSTLIBS    = -L$(BOOSTSYS)/stage/lib -lboost_iostreams -lboost_system
#-------------------------------------------------
CFLAGS      += $(ROOTCFLAGS) $(HEPCFLAGS)
LIBS         = $(ROOTLIBS) $(HEPLIBS) $(BOOSTLIBS) 

CXXFLAGS  += $(INCALL)

all: dict

$(SRC_DIR)/%.o	:  $(SRC_DIR)/%.cpp  
	$(CXX) $(CXXFLAGS) $(CFLAGS) $(OSFLAGS) -c $< -o $@ 

$(SRC_DIR)/%.o	:  $(SRC_DIR)/%.cpp  $(INC_DIR)/%.h 
	$(CXX) $(CXXFLAGS) $(CFLAGS) $(OSFLAGS) -c $< -o $@  

$(INC_DIR)/$(LIBNAME).h : $(LIBEVENT_HLISTS) $(INC_DIR)/LinkDef.h 
	rootcint -f $(LIBNAME).cpp -c -I$(INC_DIR) -I$(SRC_DIR) \
	-I$(HEP_ROOT)/include $(LIBEVENT_HLIST) $(INC_DIR)/LinkDef.h 
	mv $(LIBNAME).h $(INC_DIR)/
	mv $(LIBNAME).cpp $(SRC_DIR)/

$(SRC_DIR)/$(LIBNAME).o :  $(INC_DIR)/$(LIBNAME).h
	$(CXX) $(CFLAGS) $(OSFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/$(LIBNAME).cpp -o $@ 

$(LIB_DIR)/$(LIBNAME).so : $(LIBEVENT_LIBS)
	$(LD) $(CFLAGS) $(LDFLAGS) $(SOFLAGS) $^ -o $@ $(LIBS)

dict: 	$(LIB_DIR)/$(LIBNAME).so

$(INC_DIR)/%.h :

clean:
	rm -f $(INC_DIR)/$(LIBNAME).h
	rm -f $(SRC_DIR)/$(LIBNAME).cpp
	rm -f $(LIBEVENT_LIBS)
	rm -f $(LIB_DIR)/$(LIBNAME).so

print:
	echo $(CFLAGS)
	echo $LIBS


