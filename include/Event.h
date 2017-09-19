#ifndef __ROOT_EVENT__
#define __ROOT_EVENT__

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <vector>

#include <TNamed.h>
#include <TObject.h>
#include <TObjArray.h>
#include <TClonesArray.h>
#include <TDirectory.h>
#include <TProcessID.h>
#include <TParticle.h>
#include <TRef.h>

#include "HepMC/IO_HEPEVT.h"
#include "HepMC/GenParticle.h"
#include "HepMC/HeavyIon.h"
#include "HepMC/HEPEVT_Wrapper.h"
#include "HepMC/IO_GenEvent.h"
#include "HepMC/Units.h"
#include "HepMC/GenEvent.h"

class TDirectory;

class EventHeader{
 private:
  int             fRun;
  int             fA1Run;
  int             fA2Run;
 public:
 EventHeader(): fRun(0), fA1Run(0), fA2Run(0) { }
  virtual ~EventHeader() { }
  void            Set(int run, int a1run, int a2run) {fRun = run; fA1Run = a1run; fA2Run = a2run; }
  int             GetRun() const {return fRun;}
  int             GetA1Run() const {return fA1Run;}
  int             GetA2Run() const {return fA2Run;}

  ClassDef(EventHeader, 1)
};



class Event : public TObject{
 private:
  char           *fEventName;         //run+event number in character format
  unsigned int    fTypeID;
  int             fNtrack;
  
  EventHeader     fEvtHdr;
  TClonesArray*   fParticle;
  
  TRef            fLastParticle;
  Bool_t          fIsValid;


 public:
  Event();
  virtual ~Event();

  void            Build(int ev, HepMC::GenEvent* evt, float ptmin=1);
  Bool_t          IsValid() const {return fIsValid; }
  void            Clear(Option_t *option="");
  void            SetTypeID(unsigned int t) {fTypeID = t;}
  void            SetNtrack(int n) {fNtrack = n;}
  void            SetHeader(int run, int a1run, int a2run);
  TParticle*      AddParticle(HepMC::GenParticle* p, HepMC::GenVertex* v);

  unsigned int    GetTypeID(){return fTypeID;}
  int             GetNtrack() const {return fNtrack;}
  EventHeader*    GetHeader() {return &fEvtHdr;}
  TClonesArray*   GetParticle() const {return fParticle;}
  TParticle*      GetLastParticle() const {return (TParticle*)fLastParticle.GetObject();}
  ClassDef(Event, 1); 
};

#endif
