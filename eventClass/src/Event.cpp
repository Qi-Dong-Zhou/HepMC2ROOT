#ifndef __WRITE_EVENT__
#define __WRITE_EVENT__

#include "TDirectory.h"
#include "TProcessID.h"
#include "TMath.h"

#include "../include/Event.h"

ClassImp(Event);
ClassImp(EventHeader);


Event::Event() : fIsValid(kFALSE){
  fParticle = new TClonesArray("TParticle", 1000);

  fTypeID = 0;
  fNtrack = 0;  

  fEventName = 0;

}

Event::~Event(){
  
  Clear();
  if (fEventName) delete [] fEventName;
}

void Event::Build(int ev, HepMC::GenEvent *evt, float ptmin){
  fIsValid = kTRUE;
  //Save current Object count
  Int_t ObjectNumber = TProcessID::GetObjectCount();
  Clear();

  Int_t nch = 15;
  if (ev >= 100)   nch += 3;
  if (ev >= 10000) nch += 3;

  if (fEventName) delete [] fEventName;

  fEventName = new char[nch];

  snprintf(fEventName,nch,"Event%d",ev);
  SetTypeID( evt->signal_process_id());
  SetHeader(ev, ev, ev);
  fNtrack = 0;
  //-------------------PARTICLE LOOP
  
  //==================Sample 1 ====================
  // HepMC::GenEvent::vertex_const_iterator ver = evt->vertices_begin ();
  // for (; ver != evt->vertices_end (); ++ver){
  //   HepMC::GenVertex* v = (*ver);
  //   std::cerr<<"=================="<<v->barcode()<<"  "<<v->particles_in_size()<<"=================="<<std::endl;

  //   HepMC::GenVertex::particles_out_const_iterator par_out = v->particles_out_const_begin ();
  //   HepMC::GenVertex::particles_in_const_iterator par_in = v->particles_in_const_begin ();
  //   for (; par_out != v->particles_out_const_end (); ++par_out){
      
  //     HepMC::GenParticle* p_out = (*par_out);
  //     if (p_out->status () != 1 && p_out->status () != 2) continue; //get final state particles. status == 2 are decayed particles, status == 4 is beam particles
  //     if (TMath::Abs(p_out->momentum().eta()) < 8) continue; //Select the forward particle
  //     ++fNtrack;
  //     for (; par_in != v->particles_in_const_end (); ++par_in){
  // 	HepMC::GenParticle* p_in = (*par_in);
  // 	std::cerr<<p_in->pdg_id()<<"==="<<p_in->status()<<"++++"<<p_in->barcode()<<std::endl;
  //     }

  //     std::cerr<< p_out->pdg_id()<<"  " <<p_out->momentum().x()<<"  "<<p_out->momentum().y() << std::endl;

  //   }
  // }


  //==================Sample 2 ====================
  HepMC::GenEvent::particle_const_iterator par = evt->particles_begin ();
  for (; par != evt->particles_end (); ++par){
    HepMC::GenParticle* p = (*par);
    ++fNtrack;
    AddParticle(p);
  }

  // HepMC::GenEvent::vertex_const_iterator ver = evt->vertices_begin ();
  // for (; ver != evt->vertices_end (); ++ver){
  //   int count = 0;
  //   HepMC::GenVertex* v = (*ver);
  //   HepMC::GenVertex::particles_out_const_iterator par_out = v->particles_out_const_begin ();
  //   HepMC::GenVertex::particles_in_const_iterator par_in = v->particles_in_const_begin ();
  //   for (; par_out != v->particles_out_const_end (); ++par_out){
      
  //     HepMC::GenParticle* p_out = (*par_out);
  //     if(count == 0){
  // 	for (; par_in != v->particles_in_const_end (); ++par_in){
  // 	  HepMC::GenParticle* p_in = (*par_in);
  // 	  AddParticle(p_in, v);
  // 	  ++fNtrack;
  // 	  ++count;
  // 	  //std::cerr<<p_in->pdg_id()<<"==="<<p_in->status()<<"++++"<<p_in->barcode()<<std::endl;
  // 	}
  //     }

  //     AddParticle(p_out, v);
  //     ++fNtrack;
  //   }
  // }


  SetNtrack( fNtrack);
  //Restore Object count 
  //To save space in the table keeping track of all referenced objects
  //we assume that our events do not address each other. We reset the 
  //object count to what it was at the beginning of the event.
  TProcessID::SetObjectCount(ObjectNumber);

}

void Event::SetHeader(int run, int a1run, int a2run){
  fNtrack = 0;
  fEvtHdr.Set(run, a1run, a2run);
}

TParticle *Event::AddParticle(HepMC::GenParticle* p){

  TParticle *par = (TParticle*)fParticle->ConstructedAt(fNtrack++);

  par->SetPdgCode(p->pdg_id ());

  par->SetStatusCode(p->status ());

  par->SetMomentum(p->momentum ().px (),
              p->momentum ().py (),
              p->momentum ().pz (),
              p->momentum ().e ()
              );
  

  Bool_t  count_one = kFALSE;
  //if(p->production_vertex()){
  if(p->status() == 1 || p->status() == 2){

    for ( HepMC::GenVertex::particle_iterator ancestor 
	    = p->production_vertex()->
	    particles_begin(HepMC::ancestors);
	  ancestor != p->production_vertex()->
	    particles_end(HepMC::ancestors); 
	  ++ancestor ) {
      par->SetWeight( (*ancestor)->barcode() ); // save the barcode of origin proton: 1 or 2
      count_one = kTRUE;
      if(count_one) break;
    }
      
    for ( HepMC::GenVertex::particle_iterator mother 
	    = p->production_vertex()->
	    particles_begin(HepMC::parents);
	  mother != p->production_vertex()->
	    particles_end(HepMC::parents); 
	  ++mother ) {
      //std::cerr << (*mother)->barcode() << std::endl;
      par->SetFirstMother( (*mother)->barcode() ); // The mother only 2 in TPartilce, 
      par->SetLastMother( (*mother)->pdg_id() ); // In principe only one mother in HepMC output, first mother to save bar code, last mother to save pdg code
    }

    for ( HepMC::GenVertex::particle_iterator daughter 
	    = p->production_vertex()->
	    particles_begin(HepMC::children);
	  daughter != p->production_vertex()->
	    particles_end(HepMC::children); 
	  ++daughter ) {
      par->SetFirstDaughter( (*daughter)->barcode() ); // The mother only 2 in TPartilce, 
      par->SetLastDaughter( (*daughter)->barcode() ); // In principe only one mother in HepMC output, first mother to save bar code, last mother to save pdg code
    }
    //std::cerr << "pass" << std::endl;
    par->SetProductionVertex(p->production_vertex ()->position ().x (),
			     p->production_vertex ()->position ().y (),
			     p->production_vertex ()->position ().z (),
			     p->production_vertex ()->position ().t ()
			     );
  }
  //Add the needed particle information here

  fLastParticle = par;

  return par;
}


TParticle *Event::AddParticle(HepMC::GenParticle* p, HepMC::GenVertex* v){

  TParticle *par = (TParticle*)fParticle->ConstructedAt(fNtrack++);

  par->SetPdgCode(p->pdg_id ());

  par->SetStatusCode(p->status ());

  HepMC::GenVertex::particles_in_const_iterator par_in = v->particles_in_const_begin ();
      
  for (; par_in != v->particles_in_const_end (); ++par_in){
    HepMC::GenParticle* p_in = (*par_in);
    //std::cerr << p->barcode() << "  "  <<p_in->barcode() << "  " ;

    if(p->barcode() != p_in->barcode() && (p_in->status() == 2 || p_in->status() == 4)){ //itself is not mother particle and the mother is decayed particle
      par->SetFirstMother(p_in->barcode()); // The first mother used for matching their daughters
      par->SetMother(1, p_in->pdg_id()); // The same as SetLastMother() 
    }
    //std::cerr<<p_in->pdg_id()<<"==="<<p_in->barcode()<<std::endl;
  }
  //std::cerr << std::endl;
  
  par->SetFirstDaughter(p->barcode()); // Save its own barcode to the first daughter used for matching its mother

  par->SetMomentum(p->momentum ().px (),
              p->momentum ().py (),
              p->momentum ().pz (),
              p->momentum ().e ()
              );

  Bool_t  count_one = kFALSE;
  //if(p->production_vertex()){
  if(p->status() == 1 || p->status() == 2){
    
    for ( HepMC::GenVertex::particle_iterator ancestor 
	    = p->production_vertex()->
	    particles_begin(HepMC::ancestors);
	  ancestor != p->production_vertex()->
	    particles_end(HepMC::ancestors); 
	  ++ancestor ) {
      par->SetWeight( (*ancestor)->barcode() ); // save the barcode of origin proton: 1 or 2
      count_one = kTRUE;
      if(count_one) break;
    }
      
    for ( HepMC::GenVertex::particle_iterator mother 
	    = p->production_vertex()->
	    particles_begin(HepMC::parents);
	  mother != p->production_vertex()->
	    particles_end(HepMC::parents); 
	  ++mother ) {
      //std::cerr << (*mother)->barcode() << std::endl;
      par->SetFirstMother( (*mother)->barcode() ); // The mother only 2 in TPartilce, 
      par->SetLastMother( (*mother)->pdg_id() ); // In principe only one mother in HepMC output, first mother to save bar code, last mother to save pdg code
    }

    for ( HepMC::GenVertex::particle_iterator daughter 
	    = p->production_vertex()->
	    particles_begin(HepMC::children);
	  daughter != p->production_vertex()->
	    particles_end(HepMC::children); 
	  ++daughter ) {
      par->SetFirstDaughter( (*daughter)->barcode() ); // The mother only 2 in TPartilce, 
      par->SetLastDaughter( (*daughter)->barcode() ); // In principe only one mother in HepMC output, first mother to save bar code, last mother to save pdg code
    }
    //std::cerr << "pass" << std::endl;
    par->SetProductionVertex(p->production_vertex ()->position ().x (),
			     p->production_vertex ()->position ().y (),
			     p->production_vertex ()->position ().z (),
			     p->production_vertex ()->position ().t ()
			     );
  }
  //Add the needed particle information here

  fLastParticle = par;

  return par;
}

void Event::Clear(Option_t */*option*/){
  fParticle->Clear();
}

#endif
