# HepMC2ROOT
A library for conversion from HepMC to ROOT TTree ( header information leafs and TParticle leaf ) format, and sample codes of how to read the Tree files. For instance, you can generate PYTHIA MC with output format of HepMC (with full information), then convert the HepMC format to ROOT Tree format using this class. 
The structure of this library consist of: \
   - ./include/Event.h         // Header file of this class\ 
   - ./include/LinkDef.h       // selecting who should go into a dictionary\
   - ./src/Event.cpp           // main code of this class\
   - ./lib/libEvent.so         // created shared librar
   - Makefile\
   - ./sample/HepMC2ROOT.cpp   // example of read HepMC file write to a Tree format\
   - ./sample/sample.cpp       // example of how to read the tree format of MC output to make histograms\
