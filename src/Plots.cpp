#ifndef __PLOTS_CPP__ 
#define __PLOTS_CPP__ 

#include "../include/Plots.h"

#include <TH1F.h>
#include <TGraph2D.h>
#include <TGraph.h>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <sstream>

using namespace std;

const double Plots::XMAX_SPEC=6500.0;
//const double Plots::XMAX_SPEC=6400.0;
const double Plots::XMIN_SPEC=0.0;
const double Plots::MAX_MAP20=10.0;
const double Plots::MIN_MAP20=-10.0;
const double Plots::MAX_MAP40=20.0;
const double Plots::MIN_MAP40=-20.0;
const double Plots::d_IP1toTAN=141050;
const double Plots::XMAX_XF=1.0;
const double Plots::XMIN_XF=0.0;
const double Plots::XMAX_PT=2.0;
const double Plots::XMIN_PT=0.0;
const double Plots::XMAX_MASS=2.0;
const double Plots::XMIN_MASS=-10.0;

const double Plots::XMAX_MULTI=100.;
const double Plots::XMIN_MULTI=0.;
const double Plots::XMAX_P=50.0;
const double Plots::XMIN_P=0.0;
const double Plots::XMAX_ETA=4.;
const double Plots::XMIN_ETA=-4.;

const double Plots::XMAX_TYPE=101;
const double Plots::XMIN_TYPE=106;

const double Plots::XMAX_DIFFMASS=8000.0;
const double Plots::XMIN_DIFFMASS=0.0;

const double Plots::LOW_MASS_THRES=5.0;  //[GeV]

const double Plots::EG_THRES=200.0;  //[GeV]
const double Plots::EN_THRES=500.0;  //[GeV]

const int N_bins = 13;

//const int NDV[] = {31, 27, 40, 24, 21};
const int NDV[] = {32, 28, 41, 25, 22};

// ++++++++++++++++ Plots ++++++++++++++++++++
Plots::Plots(){
  Init();  
}

// +++++++++++++++++ ~Plots ++++++++++++++++++
Plots::~Plots(){;}

// ++++++++++++++++ Init ++++++++++++++++++++
void Plots::Init(){
  TH1::SetDefaultSumw2();

  double bins[N_bins+1] = { -9.  , -8.5  , -5.5 , -5.  , -4.5 , -4. , -3.5, -3. , -2.5, -2. ,
  			    -1.5 , -1.   , -0.5 , 0};

  double TSpE_bins[32+1] = {           0.,    200.,  300.,  400.,  500.,  600.,  700.,  800.,  900., 
                               1000., 1100., 1200., 1300., 1400., 1500., 1600., 1700., 1800., 1900.,
                               2000., 2200., 2400., 2600., 2800., 3000., 3200., 3400., 3600., 3800.,
                               4000., 4500., 5000., 6000.};
  double TLpE_bins[28+1] = {            0.,   200.,  300.,  400.,  500.,  600.,  700.,  800.,  900., 
                               1000., 1100., 1200., 1300., 1400., 1500., 1600., 1700., 1800., 1900.,
                               2000., 2200., 2400., 2600., 2800., 3000., 3500., 4000., 5000., 6000.};

 double TSnE_bins[41+1] = {            0.,    500.,  750., 1000., 1250., 1500., 1750., 2000., 2250.,
                               2500., 2750., 3000., 3250., 3500., 3750., 4000., 4250., 4500., 4750.,
                               5000., 5250., 5500., 5750., 6000., 6250., 6500., 6750., 7000., 7250.,
                               7500., 7750., 8000., 8250., 8500., 8750., 9000., 9300., 9600., 9900.,
                               10300., 10900., 17000.};
 double TL1nE_bins[25+1] = {           0.,    500.,  750., 1000., 1250., 1500., 1750., 2000., 2250.,
                               2500., 2750., 3000., 3250., 3500., 3750., 4000., 4250., 4500., 4750.,
                               5000., 5300., 5600., 6000., 6500., 7200., 15000.};
 double TL2nE_bins[22+1] = {           0.,    500.,  750., 1000., 1250., 1500., 1750., 2000., 2250.,
                               2500., 2750., 3000., 3250., 3500., 3750., 4000., 4300., 4600., 4900., 
                               5200., 5700., 6500., 13000.};

  char hname[256];
  for(int it=0; it<3; ++it){ 
    for(int icltp=0; icltp<5; icltp++){
      sprintf(hname,"h_spec_n_t%dcltp%d",it,icltp);
      //======== MC simulation for paper ================
      h_spec_n[it][icltp] = new TH1F(hname,hname, NBINS_SPEC, XMIN_SPEC, XMAX_SPEC);
      //======== MC simulation for ATLAS joint analysis ================
      // if(it == 0)
      //    h_spec_n[it][icltp] = new TH1F(hname,hname, NDV[it+2], TSnE_bins);
      // else if (it == 1)
      //    h_spec_n[it][icltp] = new TH1F(hname,hname, NDV[it+2], TL1nE_bins);
      // else
      //    h_spec_n[it][icltp] = new TH1F(hname,hname, NDV[it+2], TL2nE_bins);

      h_spec_n[it][icltp]->GetXaxis()->SetTitle("Energy [GeV]");
      h_spec_n[it][icltp]->GetYaxis()->SetTitle("dN/dE");
    }
  }

  for(int it=0; it<2; ++it){
    
    for(int icltp=0; icltp<5; icltp++){
      // -- spectrum --
      sprintf(hname,"h_spec_g_t%dcltp%d",it,icltp);
      //======== MC simulation for paper ================
      h_spec_g[it][icltp] = new TH1F(hname,hname, NBINS_SPEC, XMIN_SPEC, XMAX_SPEC);
      //======== MC simulation for ATLAS joint analysis ================
      // if(it==0)      
      // 	h_spec_g[it][icltp] = new TH1F(hname,hname, NDV[it], TSpE_bins);
      // else
      // 	h_spec_g[it][icltp] = new TH1F(hname,hname, NDV[it], TLpE_bins);

      h_spec_g[it][icltp]->GetXaxis()->SetTitle("Energy [GeV]");
      h_spec_g[it][icltp]->GetYaxis()->SetTitle("dN/dE");

    }
    // -- XF --
    for(int iptp=0; iptp<2; iptp++){
      sprintf(hname,"h_xf_t%dptp%d",it,iptp);
      h_xf[it][iptp] = new TH1D(hname,hname, NBINS_XF, XMIN_XF, XMAX_XF);
      h_xf[it][iptp]->GetXaxis()->SetTitle("X_{F}");
      h_xf[it][iptp]->GetYaxis()->SetTitle("dN/dX_{F}");
    }
    // -- hit map --
    for(int iptp=0; iptp<2; iptp++){
      sprintf(hname,"h2_hitmap_t%dptp%d",it,iptp);
      if(it==0)
	h2_hitmap[it][iptp] = new TH2D(hname,hname, NBINS_MAP20, MIN_MAP20, MAX_MAP20, NBINS_MAP20, MIN_MAP20, MAX_MAP20);
      else if(it==1)
	h2_hitmap[it][iptp] = new TH2D(hname,hname, NBINS_MAP40, MIN_MAP40, MAX_MAP40, NBINS_MAP40, MIN_MAP40, MAX_MAP40);

      h2_hitmap[it][iptp]->GetXaxis()->SetTitle("Arm1 X [mm]");
      h2_hitmap[it][iptp]->GetYaxis()->SetTitle("Arm1 Y [mm]");
    }
  }
  // -- hit map (global)--
  for(int iptp=0; iptp<2; iptp++){
    sprintf(hname,"h2_global_hitmap_ptp%d", iptp);
    h2_global_hitmap[iptp] = new TH2D(hname,hname,700,-35,35, 1000,-20,80);

    // --- Momentum ---
    sprintf(hname,"h2_pz_pt_ptp%d", iptp);
    h2_pz_pt[iptp] = new TH2D(hname,"hname", 700, 0, 7000, 200, 0, 2);
  }


  // ------- Histogram for pi ---------------
  sprintf(hname,"h2pi_global_hitmap");
  h2pi_global_hitmap = new TH2D(hname,hname,700,-35,35, 1000,-20,80);

  for(int ipitp = 0; ipitp < 3; ipitp++){
    sprintf(hname,"h2pi_pz_pt_pitp%d", ipitp);
    h2pi_pz_pt[ipitp] = new TH2D(hname,hname, 700, 0, 7000, 200, 0, 2);
  }

  sprintf(hname,"hpi_xf");
  hpi_xf = new TH1D(hname,hname, NBINS_XF, XMIN_XF, XMAX_XF);
  hpi_xf->GetXaxis()->SetTitle("X_{F}");
  hpi_xf->GetYaxis()->SetTitle("dN/dX_{F}");

  for(int it=0; it<10; ++it){
    for(int icltp=0; icltp<5; icltp++){
      sprintf(hname,"hpi_spec_t%dcltp%d",it,icltp);
      hpi_spec[it][icltp] = new TH1F(hname,hname, NBINS_SPEC, XMIN_SPEC, XMAX_SPEC);
      hpi_spec[it][icltp]->GetXaxis()->SetTitle("P_{z} [GeV]");
      hpi_spec[it][icltp]->GetYaxis()->SetTitle("dN/dP_{z}");
      // hpi_spec[it][icltp] = new TH1F(hname,hname, NBINS_PT, XMIN_PT, XMAX_PT);
      // hpi_spec[it][icltp]->GetXaxis()->SetTitle("P_{T} [GeV/c]");
      // hpi_spec[it][icltp]->GetYaxis()->SetTitle("dN/dP_{T}");
    }
  }
  

  for(int iptp=0; iptp<4; iptp++){
    sprintf(hname,"h_diff_mass_ptp%d", iptp);
    h_diff_mass[iptp] = new TH1D(hname, hname, NBINS_MASS, XMIN_MASS, XMAX_MASS);
    sprintf(hname,"h_diff_mass_lhcf_ptp%d", iptp);
    h_diff_mass_lhcf[iptp] = new TH1D(hname, hname, NBINS_MASS, XMIN_MASS, XMAX_MASS);
  }

  //=================================================
  for(int it=0; it<2; ++it){
    sprintf(hname,"h_diff_mass_g_t%d", it);
    h_diff_mass_g[it] = new TH1D(hname, hname, NBINS_DIFFMASS, XMIN_DIFFMASS, XMAX_DIFFMASS);
    for(int imass=0; imass<12; ++imass){
      sprintf(hname,"h_spec_g_mass_t%dmass%d", it, imass);
      h_spec_g_mass[it][imass] = new TH1D(hname, hname, NBINS_SPEC, XMIN_SPEC, XMAX_SPEC);
    }
  }
  for(int it=0; it<3; ++it){
    sprintf(hname,"h_diff_mass_n_t%d", it);
    h_diff_mass_n[it] = new TH1D(hname, hname, NBINS_DIFFMASS, XMIN_DIFFMASS, XMAX_DIFFMASS);
    for(int imass=0; imass<12; ++imass){
      sprintf(hname,"h_spec_n_mass_t%dmass%d", it, imass);
      h_spec_n_mass[it][imass] = new TH1D(hname, hname, NBINS_SPEC, XMIN_SPEC, XMAX_SPEC);
    }
  }
  for(int it=0; it<10; ++it){
    sprintf(hname,"hpi_diff_mass_t%d", it);
    hpi_diff_mass[it] = new TH1D(hname, hname, NBINS_DIFFMASS, XMIN_DIFFMASS, XMAX_DIFFMASS);
    for(int imass=0; imass<12; ++imass){
      sprintf(hname,"hpi_spec_mass_t%dmass%d", it, imass);
      hpi_spec_mass[it][imass] = new TH1D(hname, hname, NBINS_SPEC, XMIN_SPEC, XMAX_SPEC);
    }
  }

  h_diffmass = new TH1D("Diffractive_Mass", "Diffractive_Mass", NBINS_DIFFMASS, XMIN_DIFFMASS, XMAX_DIFFMASS );
  for(int imass=0; imass<3; imass++){
    sprintf(hname,"log10_xi_mass%d", imass);
    h_logxi[imass]  = new TH1D(hname, hname, NBINS_MASS, XMIN_MASS, XMAX_MASS);
  }
  // for(int imass=0; imass<3; imass++){
  //   sprintf(hname,"log10_xi_mass%d", imass);
  //   h_logxi[imass]  = new TH1D(hname, hname, N_bins, bins);
  // }

  // -- multiplicity, pt, eta distribution--
  for(int iptp=0; iptp<3; iptp++){
    // -- multiplicity
    sprintf(hname,"multiplicity_ptp%d", iptp);
    h_multiplicity[iptp] = new TH1D(hname,hname, NBINS_MULTI,XMIN_MULTI, XMAX_MULTI);
    sprintf(hname,"res_multiplicity_ptp%d", iptp);
    h_res_multiplicity[iptp] = new TH1D(hname,hname, NBINS_MULTI,XMIN_MULTI, XMAX_MULTI);

    // --- Momentum ---
    sprintf(hname,"momentum_ptp%d", iptp);
    h_momentum[iptp] = new TH1D(hname,hname, NBINS_P, XMIN_P, XMAX_P);
    sprintf(hname,"res_momentum_ptp%d", iptp);
    h_res_momentum[iptp] = new TH1D(hname,hname, NBINS_P, XMIN_P, XMAX_P);

    // --- eta  ---
    sprintf(hname,"eta_ptp%d", iptp);
    h_eta[iptp] = new TH1D(hname,hname, NBINS_ETA, XMIN_ETA, XMAX_ETA);
    sprintf(hname,"res_eta_ptp%d", iptp);
    h_res_eta[iptp] = new TH1D(hname,hname, NBINS_ETA, XMIN_ETA, XMAX_ETA);
  }


  // -- multiplicity, pt, eta distribution--
  for(int it=0; it<2; ++it){
    for(int iptp=0; iptp<3; iptp++){
      // -- multiplicity
      sprintf(hname,"multiplicity_t%d_ptp%d", it, iptp);
      h_multi[it][iptp] = new TH1D(hname,hname, NBINS_MULTI,XMIN_MULTI, XMAX_MULTI);
      sprintf(hname,"res_multiplicity_t%d_ptp%d", it, iptp);
      h_res_multi[it][iptp] = new TH1D(hname,hname, NBINS_MULTI,XMIN_MULTI, XMAX_MULTI);

      // --- Momentum ---
      sprintf(hname,"momentum_t%d_ptp%d", it, iptp);
      h_mom[it][iptp] = new TH1D(hname,hname, NBINS_P, XMIN_P, XMAX_P);
      sprintf(hname,"res_momentum_t%d_ptp%d", it, iptp);
      h_res_mom[it][iptp] = new TH1D(hname,hname, NBINS_P, XMIN_P, XMAX_P);

      // --- eta  ---
      sprintf(hname,"eta_t%d_ptp%d", it, iptp);
      h_eta_dist[it][iptp] = new TH1D(hname,hname, NBINS_ETA, XMIN_ETA, XMAX_ETA);
      sprintf(hname,"res_eta_t%d_ptp%d", it, iptp);
      h_res_eta_dist[it][iptp] = new TH1D(hname,hname, NBINS_ETA, XMIN_ETA, XMAX_ETA);
    }
  }
}

// // ++++++++++++++++ Fill TYPE ID++++++++++++++++++++
// void Plots::FillType(int ntracks, event* ev){
//   //int typeID = ev->GetTypeID();
//   if(ntracks == 0)
//     h_typeIDw0->Fill( ev->GetTypeID() );
//   else if (ntracks == 1)
//     h_typeIDw1->Fill( ev->GetTypeID() );
//   else if (ntracks == 2)
//     h_typeIDw2->Fill( ev->GetTypeID() );
//   else
//     h_typeIDw5->Fill( ev->GetTypeID() );
// }


// ++++++++++++++++ Fill Diffractive Mass++++++++++++++++++++
void Plots::FillInvarMass(TParticle* beam1, TParticle* beam2, double invar_mass){
  int imass = 0;
  if(invar_mass < LOW_MASS_THRES)
    imass = 1;
  else
    imass = 2;

  h_diffmass->Fill( invar_mass );
  h_logxi[0]->Fill( TMath::Log10( TMath::Power(invar_mass/(beam1->Energy() + beam2->Energy()), 2 )) );
  h_logxi[imass]->Fill( TMath::Log10( TMath::Power(invar_mass/(beam1->Energy() + beam2->Energy()), 2 )) );
}

// ++++++++++++++++ Fill Diffractive Mass++++++++++++++++++++
void Plots::FillResponseCheck( int tower, int cltp, TParticle* p, Int_t kResponse){

  int icltp = 0;

  if(cltp == 101 || cltp == 111 || cltp == 112 || cltp == 113 || cltp == 115 || cltp == 116 || cltp == 121 || cltp == 122 || cltp == 123 || cltp == 124){
    icltp = 1;
  }else{
    icltp = 2;
  }

  if(kResponse == 2){
    h_res_mom[tower][0]->Fill(p->Pt());
    h_res_eta_dist[tower][0]->Fill(p->Eta());
    if(icltp == 1){
      h_res_mom[tower][1]->Fill(p->Pt());
      h_res_eta_dist[tower][1]->Fill(p->Eta());
    }else if(icltp == 2){
      h_res_mom[tower][2]->Fill(p->Pt());
      h_res_eta_dist[tower][2]->Fill(p->Eta());
    }

  }else if (kResponse == 1){
    h_mom[tower][0]->Fill(p->Pt());
    h_eta_dist[tower][0]->Fill(p->Eta());
    if(icltp == 1){
      h_mom[tower][1]->Fill(p->Pt());
      h_eta_dist[tower][1]->Fill(p->Eta());
    }else if(icltp == 2){
      h_mom[tower][2]->Fill(p->Pt());
      h_eta_dist[tower][2]->Fill(p->Eta());
    }
  }

}

// ++++++++++++++++ Fill multiplicity++++++++++++++++++++
void Plots::FillResMultiCheck( int tower, int cltp, int nparticles, Int_t kResponse){

  int icltp = 0;

  if(cltp == 101 || cltp == 111 || cltp == 112 || cltp == 113 || cltp == 115 || cltp == 116 || cltp == 121 || cltp == 122 || cltp == 123 || cltp == 124){
    icltp = 1;
  }else{
    icltp = 2;
  }

  if(kResponse == 2){
    h_res_multi[tower][0]->Fill(nparticles);
    if(icltp == 1){
      h_res_multi[tower][1]->Fill(nparticles);
    }else if(icltp == 2){
      h_res_multi[tower][2]->Fill(nparticles);
    }

  }else if (kResponse == 1){
    h_multi[tower][0]->Fill(nparticles);
    if(icltp == 1){
      h_multi[tower][1]->Fill(nparticles);
    }else if(icltp == 2){
      h_multi[tower][2]->Fill(nparticles);
    }
  }

}

// ++++++++++++++++ Fill multiplicity++++++++++++++++++++
void Plots::FillResMulti( int cltp, int nparticles, Int_t kResponse){

  int icltp = 0;

  if(cltp == 101 || cltp == 111 || cltp == 112 || cltp == 113 || cltp == 115 || cltp == 116 || cltp == 121 || cltp == 122 || cltp == 123 || cltp == 124){
    icltp = 1;
  }else{
    icltp = 2;
  }

  if(kResponse == 2){
    h_res_multiplicity[0]->Fill(nparticles);
    if(icltp == 1){
      h_res_multiplicity[1]->Fill(nparticles);
    }else if(icltp == 2){
      h_res_multiplicity[2]->Fill(nparticles);
    }

  }else if (kResponse == 1){
    h_multiplicity[0]->Fill(nparticles);
    if(icltp == 1){
      h_multiplicity[1]->Fill(nparticles);
    }else if(icltp == 2){
      h_multiplicity[2]->Fill(nparticles);
    }
  }

}



// ++++++++++++++++ Fill Diffractive Mass++++++++++++++++++++
void Plots::FillDiffMassFiducial(int tower, int iptp, double diff_mass, TParticle* p){
  
  int imass = 0;
  if(diff_mass < LOW_MASS_THRES)
    imass = 1;
  else
    imass = 2;

    
  if(iptp == 22){
    h_diff_mass_g[tower]->Fill( diff_mass );

    h_spec_g_mass[tower][0]->Fill( p->Energy() );
    h_spec_g_mass[tower][imass]->Fill( p->Energy() );
  }else if(iptp == 2112){
    h_diff_mass_n[tower]->Fill( diff_mass );

    h_spec_n_mass[tower][0]->Fill( p->Energy() );
    h_spec_n_mass[tower][imass]->Fill( p->Energy() );
  }
}
// ++++++++++++++++ Fill Diffractive Mass++++++++++++++++++++
void Plots::FillLogxiFiducial(int tower, int iptp, double logxi, TParticle* p){

  int imass = 0;

  if(logxi < -7.75)
    imass = 1;
  else if (logxi>= -7.75 && logxi <=-7.5)
    imass = 2;
  else if (logxi>= -7.5 && logxi <=-7.25)
    imass = 3;
  else if (logxi>= -7.25 && logxi <=-7.0)
    imass = 4;
  else if (logxi>= -7.0 && logxi <=-6.75)
    imass = 5;
  else if (logxi>= -6.75 && logxi <=-6.5)
    imass = 6;
  else if (logxi>= -6.5 && logxi <=-6.25)
    imass = 7;
  else if (logxi>= -6.25 && logxi <=-6.0)
    imass = 8;
  else if (logxi>= -6.0 && logxi <=-5.5)
    imass = 9;
  else if (logxi>= -5.5 && logxi <=-5.0)
    imass = 10;
  else if (logxi>= -5.0)
    imass = 11;
  

    
  if(iptp == 22){

    h_spec_g_mass[tower][0]->Fill( p->Energy() );
    h_spec_g_mass[tower][imass]->Fill( p->Energy() );
  }else if(iptp == 2112){

    h_spec_n_mass[tower][0]->Fill( p->Energy() );
    h_spec_n_mass[tower][imass]->Fill( p->Energy() );
  }
}
// ++++++++++++++++ Fill Diffractive Mass++++++++++++++++++++
void Plots::FillLogxiPi0Fiducial(double logxi, TParticle* p){
  double pt = TMath::Sqrt( p->Px()*p->Px() + p->Py()*p->Py() );

  int imass = 0;
  if(logxi < -7.75)
    imass = 1;
  else if (logxi>= -7.75 && logxi <=-7.5)
    imass = 2;
  else if (logxi>= -7.5 && logxi <=-7.25)
    imass = 3;
  else if (logxi>= -7.25 && logxi <=-7.0)
    imass = 4;
  else if (logxi>= -7.0 && logxi <=-6.75)
    imass = 5;
  else if (logxi>= -6.75 && logxi <=-6.5)
    imass = 6;
  else if (logxi>= -6.5 && logxi <=-6.25)
    imass = 7;
  else if (logxi>= -6.25 && logxi <=-6.0)
    imass = 8;
  else if (logxi>= -6.0 && logxi <=-5.5)
    imass = 9;
  else if (logxi>= -5.5 && logxi <=-5.0)
    imass = 10;
  else if (logxi>= -5.0)
    imass = 11;

  int neta = 9;
  //double eta = p->Y();  // rapidity not pesidorapidity
  for(int ieta = 0; ieta<10; ieta++){
    double down = ieta*0.2;
    double up   = (ieta+1)*0.2;
    if(pt >= down && pt < up)            //change rapidity to pt
      neta = ieta;
  }

  hpi_spec_mass[neta][0]->Fill( p->Pz() );
  hpi_spec_mass[neta][imass]->Fill( p->Pz() );
    

}


void Plots::FillDiffMassPi0(double logxi, TParticle* p){

  h_diff_mass[2]->Fill( logxi );
  if(p->Y()>8.4 && p->Y()<10.8){
    h_diff_mass_lhcf[2]->Fill( logxi );
  }

}
void Plots::FillDiffMassPi0Fiducial(double diff_mass, TParticle* p){
  double pt = TMath::Sqrt( p->Px()*p->Px() + p->Py()*p->Py() );

  int imass = 0;
  if(diff_mass < LOW_MASS_THRES)
    imass = 1;
  else
    imass = 2;

  int neta = 9;
  //double eta = p->Y();  // rapidity not pesidorapidity
  for(int ieta = 0; ieta<10; ieta++){
    double down = ieta*0.2;
    double up   = (ieta+1)*0.2;
    if(pt >= down && pt < up)            //change rapidity to pt
      neta = ieta;
  }

  hpi_diff_mass[neta]->Fill(diff_mass);
  hpi_spec_mass[neta][0]->Fill( p->Pz() );
  hpi_spec_mass[neta][imass]->Fill( p->Pz() );
}


// ++++++++++++++++ Fill ++++++++++++++++++++
void Plots::Fill(int tower, int cltp, int iptp, TParticle* p){
  int icltp = 0;

  //if(cltp == 101){//change for single parton collisions in 30 Aug 2016
  if(cltp == 101 || cltp == 111 || cltp == 112 || cltp == 113 || cltp == 115 || cltp == 116 || cltp == 121 || cltp == 122 || cltp == 123 || cltp == 124){
    icltp = 1;
  }else{
    icltp = 2;
  }
  // -- energy spectrum --
  if(iptp == 22){
    if (tower == 2) tower = 1;
    h_spec_g[tower][0]->Fill( p->Energy() );
    h_spec_g[tower][icltp]->Fill( p->Energy() );
  }else if(iptp == 2112){
    h_spec_n[tower][0]->Fill( p->Energy() );
    h_spec_n[tower][icltp]->Fill( p->Energy() );
  }
  // // -- hitmap --
  // double cal_x = sel->CalPos(p, tower, 0);
  // double cal_y = sel->CalPos(p, tower, 1);
  // sel->GetPosition(p, x, y);
  // if(iptp == 22){
  //   if (tower == 2) tower = 1;
  //   h2_hitmap[tower][0]->Fill( cal_x, cal_y );
  //   h2_global_hitmap[0]->Fill(x, y);
  // }else if(iptp == 2112){
  //   h2_hitmap[tower][1]->Fill( cal_x, cal_y );
  //   h2_global_hitmap[1]->Fill(x, y);
  // }

  // --- Momentum calculation ---
  double pt = TMath::Sqrt( p->Px()*p->Px() + p->Py()*p->Py() );
  //double xf = 2*p->Pz()/TMath::Sqrt(13000.0);
  double xf = p->Pz()/6500.0;
  if(iptp == 22){
    if (tower == 2) tower = 1;
    h2_pz_pt[0]->Fill( p->Pz(), pt );
    // -- XF --
    h_xf[tower][0]->Fill( xf );
  }else if(iptp == 2112){
    h2_pz_pt[1]->Fill( p->Pz(), pt );
    // -- XF --
    h_xf[tower][1]->Fill( xf );
  }
}


// ++++++++++++++++ Fill ++++++++++++++++++++
void Plots::Fill(int tower, int cltp, int iptp, TParticle* p, double weight){
  int icltp = 0;

  //if(cltp == 101){//change for single parton collisions in 30 Aug 2016
  if(cltp == 101 || cltp == 111 || cltp == 112 || cltp == 113 || cltp == 115 || cltp == 116 || cltp == 121 || cltp == 122 || cltp == 123 || cltp == 124){
    icltp = 1;
  }else{
    icltp = 2;
  }
  // -- energy spectrum --
  if(iptp == 22){
    if (tower == 2) tower = 1;
    h_spec_g[tower][0]->Fill( p->Energy(), weight );
    h_spec_g[tower][icltp]->Fill( p->Energy(), weight );
  }else if(iptp == 2112){
    h_spec_n[tower][0]->Fill( p->Energy(), weight );
    h_spec_n[tower][icltp]->Fill( p->Energy(), weight );
  }
  // // -- hitmap --
  // double cal_x = sel->CalPos(p, tower, 0);
  // double cal_y = sel->CalPos(p, tower, 1);
  // sel->GetPosition(p, x, y);
  // if(iptp == 22){
  //   if (tower == 2) tower = 1;
  //   h2_hitmap[tower][0]->Fill( cal_x, cal_y );
  //   h2_global_hitmap[0]->Fill(x, y);
  // }else if(iptp == 2112){
  //   h2_hitmap[tower][1]->Fill( cal_x, cal_y );
  //   h2_global_hitmap[1]->Fill(x, y);
  // }

  // --- Momentum calculation ---
  double pt = TMath::Sqrt( p->Px()*p->Px() + p->Py()*p->Py() );
  //double xf = 2*p->Pz()/TMath::Sqrt(13000.0);
  double xf = p->Pz()/6500.0;
  if(iptp == 22){
    if (tower == 2) tower = 1;
    h2_pz_pt[0]->Fill( p->Pz(), pt );
    // -- XF --
    h_xf[tower][0]->Fill( xf );
  }else if(iptp == 2112){
    h2_pz_pt[1]->Fill( p->Pz(), pt );
    // -- XF --
    h_xf[tower][1]->Fill( xf );
  }
}

// ++++++++++++++++ Draw ++++++++++++++++++++
void Plots::Draw(){

  TCanvas* can = new TCanvas();
  // -- 20mm --
  can->Divide(2,3);
  can->cd(1);
  gPad->SetLogy(1);
  h_spec_g[0][0]->Draw();
  can->cd(3);
  h2pi_pz_pt[0]->Draw("colz");
  can->cd(5);
  h2_hitmap[0][0]->Draw("colz");
  // -- 40mm --
  can->cd(2);
  gPad->SetLogy(1);
  h_spec_n[1][0]->Draw();
  can->cd(4);
  h_xf[1][0]->Draw();
  can->cd(6);
  h2_hitmap[1][0]->Draw("colz");

  TCanvas* cg = new TCanvas("global_hitmap","global_hitmap",600,900);
  cg->SetLeftMargin(0.12);
  h2_global_hitmap[0]->SetStats(0);
  h2_global_hitmap[0]->GetXaxis()->SetTitle("x [mm]");
  h2_global_hitmap[0]->GetYaxis()->SetTitle("y [mm]");
  h2_global_hitmap[0]->GetYaxis()->SetTitleOffset(1.2);
  h2_global_hitmap[0]->Draw("colz");

}


// ++++++++++++++++ WriteROOTfile ++++++++++++++++++++
void Plots::WriteROOTfile(char* filename){

  TFile* fout = new TFile(filename,"recreate");
  for(int it=0; it<3; ++it){
    for(int icltp=0; icltp<5; icltp++){
      h_spec_n[it][icltp]->Write();      
    }
  }
  for(int it=0; it<2; ++it){
    for(int icltp=0; icltp<5; icltp++){
      h_spec_g[it][icltp]->Write();
    }

    h2_hitmap[it][0]->Write();
    h2_hitmap[it][1]->Write();
      
    h2_global_hitmap[it]->Write();
    h2_pz_pt[it]->Write();

    h_xf[it][0]->Write();
    h_xf[it][1]->Write();
  }

  for(int ieta=0; ieta<10; ieta++){
    for(int icltp=0; icltp<5; icltp++){
      hpi_spec[ieta][icltp]->Write();
    }
  }

  h2pi_global_hitmap->Write();
  for(int ipitp=0; ipitp<3; ipitp++){
    h2pi_pz_pt[ipitp]->Write();
  }

  hpi_xf->Write();

  fout->Write();
}

#endif
