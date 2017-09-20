#ifndef __PLOTS_H__ 
#define __PLOTS_H__ 

#include <TObject.h>
#include <TFile.h>
#include <TCanvas.h>
#include <string>
#include <TH1D.h>
#include <TH2D.h>
#include <TH1F.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TParticle.h>


using namespace std;

class Plots{

 public:
  static const int NBINS_SPEC=26;
  //static const int NBINS_SPEC=32;
  static const double XMAX_SPEC;
  static const double XMIN_SPEC;
  static const int NBINS_MAP20=200;
  static const double MAX_MAP20;
  static const double MIN_MAP20;
  static const int NBINS_MAP40=400;
  static const double MAX_MAP40;
  static const double MIN_MAP40;
  static const double d_IP1toTAN;
  static const int NBINS_XF=20;
  static const double XMAX_XF;
  static const double XMIN_XF;
  static const int NBINS_PT=40;
  static const double XMAX_PT;
  static const double XMIN_PT;
  //static const int NBINS_MASS=60;
  static const int NBINS_MASS=120;
  static const double XMAX_MASS;
  static const double XMIN_MASS;
  static const int NBINS_DIFFMASS=8000;
  static const double XMAX_DIFFMASS;
  static const double XMIN_DIFFMASS;

  static const int NBINS_MULTI=100;
  static const double XMAX_MULTI;
  static const double XMIN_MULTI;
  static const int NBINS_P=500;
  static const double XMAX_P;
  static const double XMIN_P;
  static const int NBINS_ETA=80;
  static const double XMAX_ETA;
  static const double XMIN_ETA;

  static const double LOW_MASS_THRES;
  static const int NBINS_TYPE=5;
  static const double XMAX_TYPE;
  static const double XMIN_TYPE;
  static const double EG_THRES;
  static const double EN_THRES;
  double x, y;

  TH1F* h_spec_g[2][5];      //[tower][collision type]
  TH1F* h_spec_n[3][5];      //[tower][collision type]

  TH2D* h2_hitmap[2][2];     //[tower][particle type]
  TH2D* h2_global_hitmap[2]; //[particle type]
  TH2D* h2_pz_pt[2];         //[particle type]
  TH1D* h_xf[2][2];          //[tower][particle type]
   
  TH1D* h_diff_mass[4];            //[particle type]
  TH1D* h_diff_mass_lhcf[4];        //[particle type]

  //TH1D* h_spec_g_mass[2][3];    //[tower][particle type]
  //TH1D* h_spec_n_mass[3][3];    //[tower][particle type]
  
  TH1D* h_spec_g_mass[2][12];    //[tower][particle type]
  TH1D* h_spec_n_mass[3][12];    //[tower][particle type]
  
  TH1D* h_diff_mass_g[2];          //[tower][particle type]
  TH1D* h_diff_mass_n[3];          //[tower][particle type]


  TH1F* hpi_spec[10][5];      //[rapidity][collision type][pi0 type]
  TH2D* h2pi_global_hitmap;   //[particle type]
  TH2D* h2pi_pz_pt[3];        //[particle type]
  TH1D* hpi_xf;               //[tower][particle type]
  TH1D* hpi_diff_mass[10];     //[tower][particle type]
  //TH1D* hpi_spec_mass[10][3];    //[tower][particle type]
  TH1D* hpi_spec_mass[10][12];    //[tower][particle type]

  TH1D* h_diffmass;          
  TH1D* h_logxi[3];         

  TH1D* h_multiplicity[3];         
  TH1D* h_res_multiplicity[3];         

  TH1D* h_momentum[3];         
  TH1D* h_res_momentum[3];

  TH1D* h_eta[3];         
  TH1D* h_res_eta[3];
         
  TH1D* h_multi[2][3];         
  TH1D* h_res_multi[2][3];         

  TH1D* h_mom[2][3];         
  TH1D* h_res_mom[2][3];

  TH1D* h_eta_dist[2][3];         
  TH1D* h_res_eta_dist[2][3];
         
  TCanvas* can[10];
  
 private:  

 public:
  Plots();
  virtual ~Plots();

  void Init();
  void Fill(int tower, int cltp, int iptp,  TParticle* p);
  void Fill(int tower, int cltp, int iptp,  TParticle* p, double weight);
  void FillResponse(int cltp, TParticle* p, Int_t kResponse);
  void FillResMulti(int cltp, int nparticles, Int_t kResponse);
  void FillResponseCheck(int tower, int cltp, TParticle* p, Int_t kResponse);
  void FillResMultiCheck(int tower, int cltp, int nparticles, Int_t kResponse);
  void FillLog10Xi(TParticle* beam1, TParticle* beam2, TParticle* p);
  void FillInvarMass(TParticle* beam1, TParticle* beam2, double invar_mass);
  void FillDiffMass(int iptp, double logxi, TParticle* p);
  void FillDiffMassPi0(double logxi, TParticle* p);
  void FillDiffMassFiducial(int tower, int iptp, double diff_mass, TParticle* p);
  void FillDiffMassPi0Fiducial(double diff_mass, TParticle* p);
  void FillLogxiFiducial(int tower, int iptp, double logxi, TParticle* p);
  void FillLogxiPi0Fiducial(double logxi, TParticle* p);
  void Draw();
  void WriteROOTfile(char* filename);
};

#endif
