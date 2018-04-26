#include <algorithm>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string.h>
#include <sstream>
#include <fstream>
#include <math.h>
#include <stdlib.h>


#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include <boost/format.hpp>
#include <boost/program_options.hpp>


#include "HepMC/IO_HEPEVT.h"
#include "HepMC/GenParticle.h"
#include <HepMC/HeavyIon.h>
#include "HepMC/HEPEVT_Wrapper.h"
#include "HepMC/IO_GenEvent.h"
#include "HepMC/Units.h"
#include "HepMC/GenEvent.h"

#include <Riostream.h>
#include <TFile.h>
#include <TH1D.h>
#include <TTree.h>
#include "TBranch.h"
#include "TClonesArray.h"
#include "TProcessID.h"
#include "TROOT.h"


#include "analysis.h"
#include "Event.h"

namespace io = boost::iostreams;
using namespace std;

int nfile = 0;

void print_help(){
  cout << "./bin/HepMC2ROOT \n"
       << " Convert the MC data from HepMC format to ROOT\n"
       << " ./bin/HepMC2ROOT  --file xxx \n"
       << endl;
  return ;
}

void argument(int argc, char **argv){

  for(int i=1;i<argc;i++){
    string ss = argv[i];
    if(ss=="--file"){
      nfile = atoi(argv[++i]);
    }
    if(ss=="--help" || ss=="-h"){
      print_help();
      return;
    }
  }
}


int main (int argc, char **argv){

  argument(argc, argv);

  //-------------------SET UP DATA
  vector<string> filesModel1;
  //=============PYTHIA8212==============
  //filesModel1.push_back (Form("/Path/to/HepMC/data/pythia%03d.hepmc.gz",nfile)); //add your files here with additional push_back()
  filesModel1.push_back (Form("/mnt/lhcfs3/data4/Zhou/Simulation/LHC/pp13TeV/SIBYLL2.3c_mod/crmc_sibyll%03d.hepmc.gz",nfile)); //add your files here with additional push_back()


  DataManager data;
  data.SetFiles (filesModel1); //for more models, loop over models and call SetFiles each time
  //theOutFile->mkdir ("model1");

  TTree *tree;
  Event *event = 0;

  TFile* theOutFile;
  char outFileName[256];
  //sprintf(outFileName, "/Path/to/save/ROOT/file/PYTHIA8212/pythia%03d.root", nfile);
  sprintf(outFileName, "/mnt/lhcfs3/data4/Zhou/Simulation/LHC/pp13TeV/SIBYLL2.3c_mod/sibyll%03d.root", nfile);
  cout << " ! Opening output file: " << outFileName << endl;
  theOutFile = new TFile(outFileName, "RECREATE");
  //theOutFile->SetCompressionLevel(1);

  Long64_t nb = 0;
  tree = new TTree("T", "MC samples with selections");
  tree->SetAutoSave(1000000000);
  tree->SetCacheSize(10000000);
  Int_t split = 1;
  Int_t bufsize = 64000;
  if(split) bufsize /= 4;
  Int_t branchStyle = 0;
  event = new Event();
  TTree::SetBranchStyle(branchStyle);
  TBranch *branch = tree->Branch("event", &event, bufsize, split);
  branch->SetAutoDelete(kFALSE);
  if(split >= 0 && branchStyle) tree->BranchRef();
  float ptmin = 1;

//-------------------EVENT LOOP
  int nEvts = 0;
  while (data.GetNextEvent ())
    {
      // bool track_flag = false;
      // HepMC::GenEvent::particle_const_iterator par = data.evt->particles_begin ();
      // for (; par != data.evt->particles_end (); ++par){
      // 	HepMC::GenParticle* p = (*par);
      // 	if (p->status () != 1 && p->status () != 2) continue; //get final state particles. status == 2 are decayed particles, status == 4 is beam particles
      // 	if (TMath::Abs(p->momentum().eta()) > 8) track_flag = true; //Select the forward particle
	
      // 	if (track_flag == true) break;
	
      // }

      // if (track_flag == true){ // select the events has forward particle
	++nEvts;
	event->Build(nEvts, data.evt, ptmin);
	nb += tree->Fill();
	//}
    }//EVENT LOOP
  
  //----------------Closing Files
  std::cout << " ! Writing output file: " << outFileName << std::endl;
  theOutFile = tree->GetCurrentFile();
  theOutFile->Write();
  //tree->Print();  
  delete event; event=0;
  std::cout << " ! Closing output file: " << outFileName << std::endl;
  theOutFile->Close();
  return 0;
}
