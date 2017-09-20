// ================================================================================================
//                                                                                               ==
// Sample of reading data with format of ROOT tree ( made by using eventClass in this directory) ==
// First Edited by Qi-Dong Zhou on Apr 2016                                                      ==
//                                                                                               == 
// ================================================================================================
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <TROOT.h>
#include <TRint.h>
#include <TH1D.h>
#include <TH1F.h>
#include <TH2D.h>
#include <TH2F.h>
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TBranch.h"
#include "TClonesArray.h"
#include "TParticle.h"

#include "Event.h"
#include "Plots.h"

#include <omp.h>

using namespace std;

Event *event = 0;
Plots *plot = 0;

int file_first = 0;
int file_last = 1;

void print_help(){
  cout << "./bin/ReadSample \n"
       << " Read the MC data from root format file\n"
       << " ./ReadSample  --file xxx xxx \n"
       << endl;
  return ;
}

void argument(int argc, char **argv){

  for(int i=1;i<argc;i++){
    string ss = argv[i];
    if(ss=="--file"){
      file_first = atoi(argv[++i]);
      file_last  = atoi(argv[++i]);
    }

    if(ss=="--help" || ss=="-h"){
      print_help();
      return;
    }
  }
}

void initializations(){
  // --- ---
  event = new Event();
  plot  = new Plots();
}

int main(int argc, char** argv){
  argument(argc, argv);
  
  TRint theApp("App",&argc,argv,0,0,kTRUE);
  // --- for analysis classes ---
  initializations();


  vector<string> ifilenames;
  char filename[256];

  double start = omp_get_wtime();
  // ======= INPUT FILE HERE ========

  for(int i=file_first; i<=file_last; ++i){
      sprintf(filename,"/Path/to/ROOT/data/PYTHIA8212/pythia%03d.root",i);
    ifilenames.push_back(filename);
  }

  TChain* tree = new TChain("T","");
  for(int i=0; i<(int)ifilenames.size(); ++i){
    tree->AddFile(ifilenames[i].c_str());
  }
  tree->SetBranchAddress("event", &event);

  //======================
  //== EVENT LOOP START ==
  //======================

  vector <TParticle*> pg20;
  vector <TParticle*> pg40;

  Long64_t nb = 0;
  Int_t nentries = tree->GetEntriesFast();
  
  for (int ev = 0; ev < nentries; ev++) {
    
    if(ev!=0 && ev%200==0){ cout << '*' ; }
    if(ev!=0 && ev%5000==0){ cout << ev << endl; }
    
    Int_t ientry = tree->LoadTree(ev);  //this call is required when using the cache
    if(ientry < 0) break;

    nb += tree->GetEntry(ev);        //read complete event in memory

    //====Fill the histogram of photon=====
    for(int tr = 0; tr<event->GetParticle()->GetEntriesFast(); tr++){
      TParticle* part = (TParticle*)event->GetParticle()->ConstructedAt(tr);
      if(part->GetPdgCode() == -9999 ) continue;
      // === Implement the selection condition =========
      // === Fill the histogram defined in Plot.cpp ====
      plot->Fill(1, event->GetTypeID(), part->GetPdgCode(), part);

    }    
    event->Clear("C");
  }
  //====================
  //== EVENT LOOP END ==
  //====================
  double end = omp_get_wtime();
  cerr << "Time passed: " << end-start << endl;
  
  plot->Draw();

  char ofilename[256];
  sprintf(ofilename, "./data/PYTHIA8212.root");
  plot->WriteROOTfile(ofilename);

  theApp.Run();

  return 0;

}
//------------------------------------------------
//          Functions for this code
//------------------------------------------------
