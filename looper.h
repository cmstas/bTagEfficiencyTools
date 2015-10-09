#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TH2.h"

#include "Math/VectorUtil.h"
#include "Math/LorentzVector.h"

// typedefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;


#ifndef LOOPER_H
#define LOOPER_H

#pragma GCC diagnostic ignored "-Wwrite-strings"

using namespace std;

const double eps=0.000001;

class bTagEffMaker{

  public:
    
    // Variable for output directory
    char* bTagEffPath;
    
    // Variables for btag eff maker
    double skim_jet_pt;
    double skim_jet_eta;

    double csv_wp_loose;
    double csv_wp_med;
    double csv_wp_tight;

    int nBins_pt;
    int nBins_eta;

    double pt_min;
    double pt_max;
    double *pt_bins;

    double eta_min;
    double eta_max;
    double *eta_bins;

    int nBins_pt_fine;
    int nBins_eta_fine;

    double pt_min_fine;
    double pt_max_fine;
    double *pt_bins_fine;

    double eta_min_fine;
    double eta_max_fine;
    double *eta_bins_fine;
    
    // Constructor/destructor
    bTagEffMaker ();
    virtual ~bTagEffMaker (){}

    // Functions
    void MakeBTagEffNtuple(const char* output_name);
 
    void setSkimVariables(double jet_pt, double jet_eta, double csv_loose, double csv_med, double csv_tight, int Pt_nBins, double Pt_min, double Pt_max, double *Pt_bins, int Eta_nBins, double Eta_min, double Eta_max, double *Eta_bins, int Pt_nBins_fine, double Pt_min_fine, double Pt_max_fine, double *Pt_bins_fine, int Eta_nBins_fine, double Eta_min_fine, double Eta_max_fine, double *Eta_bins_fine);
    
    int looper(TChain* chain, char* output_name, int nEvents = -1, char* path = "./");
    

  protected:
    TFile* BTagEffFile;
    
  private:

    // Histos for bTag Eff
    TH2D *h2_BTaggingEff_csv_Denom_b;
    TH2D *h2_BTaggingEff_csv_Denom_c;
    TH2D *h2_BTaggingEff_csv_Denom_udsg;
    
    
    TH2D *h2_BTaggingEff_csv_loose_Num_b;
    TH2D *h2_BTaggingEff_csv_loose_Num_c;
    TH2D *h2_BTaggingEff_csv_loose_Num_udsg;
    
    TH2D *h2_BTaggingEff_csv_med_Num_b;
    TH2D *h2_BTaggingEff_csv_med_Num_c;
    TH2D *h2_BTaggingEff_csv_med_Num_udsg;
    
    TH2D *h2_BTaggingEff_csv_tight_Num_b;
    TH2D *h2_BTaggingEff_csv_tight_Num_c;
    TH2D *h2_BTaggingEff_csv_tight_Num_udsg;


    // Fine Binning
    TH2D *h2_BTaggingEff_csv_fineBinning_Denom_b;
    TH2D *h2_BTaggingEff_csv_fineBinning_Denom_c;
    TH2D *h2_BTaggingEff_csv_fineBinning_Denom_udsg;
    
    
    TH2D *h2_BTaggingEff_csv_fineBinning_loose_Num_b;
    TH2D *h2_BTaggingEff_csv_fineBinning_loose_Num_c;
    TH2D *h2_BTaggingEff_csv_fineBinning_loose_Num_udsg;
    
    TH2D *h2_BTaggingEff_csv_fineBinning_med_Num_b;
    TH2D *h2_BTaggingEff_csv_fineBinning_med_Num_c;
    TH2D *h2_BTaggingEff_csv_fineBinning_med_Num_udsg;
    
    TH2D *h2_BTaggingEff_csv_fineBinning_tight_Num_b;
    TH2D *h2_BTaggingEff_csv_fineBinning_tight_Num_c;
    TH2D *h2_BTaggingEff_csv_fineBinning_tight_Num_udsg;

    

};

struct val_err_t { float value; float error; };

#endif
