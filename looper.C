#include <string.h>
#include <iostream>
#include <vector>
#include <typeinfo>

#include "looper.h"

#include "TBenchmark.h"
#include "TChain.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TROOT.h"
#include "TTreeCache.h"
#include "TH1.h"
#include "TH2.h"

#include "CMS3.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

using namespace std;
using namespace tas;


//====================//
//                    //
// Utility Structures //
//                    //
//====================//

struct sortbypt{
  bool operator () (const pair<int, LorentzVector> &v1, const pair<int,LorentzVector> &v2){
    return v1.second.pt() > v2.second.pt();
  }
};


//===========//
//           //
// Functions //
//           //
//===========//

bTagEffMaker::bTagEffMaker(){

    
}

void bTagEffMaker::setSkimVariables(double jet_pt, double jet_eta, double csv_loose, double csv_med, double csv_tight, int Pt_nBins, double Pt_min, double Pt_max, double *Pt_bins, int Eta_nBins, double Eta_min, double Eta_max, double *Eta_bins, int Pt_nBins_fine, double Pt_min_fine, double Pt_max_fine, double *Pt_bins_fine, int Eta_nBins_fine, double Eta_min_fine, double Eta_max_fine, double *Eta_bins_fine){

  skim_jet_pt  = jet_pt;
  skim_jet_eta = jet_eta;

  csv_wp_loose = csv_loose;
  csv_wp_med   = csv_med;
  csv_wp_tight = csv_tight;

  nBins_pt = Pt_nBins;
  pt_min   = Pt_min;
  pt_max   = Pt_max;
  pt_bins  = Pt_bins;

  nBins_eta = Eta_nBins;
  eta_min   = Eta_min;
  eta_max   = Eta_max;
  eta_bins  = Eta_bins;

  nBins_pt_fine = Pt_nBins_fine;
  pt_min_fine   = Pt_min_fine;
  pt_max_fine   = Pt_max_fine;
  pt_bins_fine  = Pt_bins_fine;

  nBins_eta_fine = Eta_nBins_fine;
  eta_min_fine   = Eta_min_fine;
  eta_max_fine   = Eta_max_fine;
  eta_bins_fine  = Eta_bins_fine;

  
  return;
    
}


void bTagEffMaker::MakeBTagEffNtuple(const char* output_name){

  BTagEffFile = new TFile(Form("%s/%s", bTagEffPath, output_name), "RECREATE");

  // Nominal Binning
  h2_BTaggingEff_csv_Denom_b = new TH2D("h2_BTaggingEff_csv_Denom_b", "b-tagging effiency, Denominator, MC, CSV, b-jets, #eta vs p_{T};p_{T};#eta", nBins_pt, pt_bins, nBins_eta, eta_bins);
  h2_BTaggingEff_csv_Denom_c = new TH2D("h2_BTaggingEff_csv_Denom_c", "b-tagging effiency, Denominator, MC, CSV loose, c-jets, #eta vs p_{T};p_{T};#eta", nBins_pt, pt_bins, nBins_eta, eta_bins);
  h2_BTaggingEff_csv_Denom_udsg = new TH2D("h2_BTaggingEff_csv_Denom_udsg", "b-tagging effiency, Denominator, MC, CSV loose, udsg-jets, #eta vs p_{T};p_{T};#eta", nBins_pt, pt_bins, nBins_eta, eta_bins);

  h2_BTaggingEff_csv_loose_Num_b = new TH2D("h2_BTaggingEff_csv_loose_Num_b", "b-tagging effiency, Numerator, MC, CSV loose, b-jets, #eta vs p_{T};p_{T};#eta", nBins_pt, pt_bins, nBins_eta, eta_bins);
  h2_BTaggingEff_csv_loose_Num_c = new TH2D("h2_BTaggingEff_csv_loose_Num_c", "b-tagging effiency, Numerator, MC, CSV loose, c-jets, #eta vs p_{T};p_{T};#eta", nBins_pt, pt_bins, nBins_eta, eta_bins);
  h2_BTaggingEff_csv_loose_Num_udsg = new TH2D("h2_BTaggingEff_csv_loose_Num_udsg", "b-tagging effiency, Numerator, MC, CSV loose, udsg-jets, #eta vs p_{T};p_{T};#eta", nBins_pt, pt_bins, nBins_eta, eta_bins);


  h2_BTaggingEff_csv_med_Num_b = new TH2D("h2_BTaggingEff_csv_med_Num_b", "b-tagging effiency, Numerator, MC, CSV med, b-jets, #eta vs p_{T};p_{T};#eta", nBins_pt, pt_bins, nBins_eta, eta_bins);
  h2_BTaggingEff_csv_med_Num_c = new TH2D("h2_BTaggingEff_csv_med_Num_c", "b-tagging effiency, Numerator, MC, CSV med, c-jets, #eta vs p_{T};p_{T};#eta", nBins_pt, pt_bins, nBins_eta, eta_bins);
  h2_BTaggingEff_csv_med_Num_udsg = new TH2D("h2_BTaggingEff_csv_med_Num_udsg", "b-tagging effiency, Numerator, MC, CSV med, udsg-jets, #eta vs p_{T};p_{T};#eta", nBins_pt, pt_bins, nBins_eta, eta_bins);


  h2_BTaggingEff_csv_tight_Num_b = new TH2D("h2_BTaggingEff_csv_tight_Num_b", "b-tagging effiency, Numerator, MC, CSV tight, b-jets, #eta vs p_{T};p_{T};#eta", nBins_pt, pt_bins, nBins_eta, eta_bins);
  h2_BTaggingEff_csv_tight_Num_c = new TH2D("h2_BTaggingEff_csv_tight_Num_c", "b-tagging effiency, Numerator, MC, CSV tight, c-jets, #eta vs p_{T};p_{T};#eta", nBins_pt, pt_bins, nBins_eta, eta_bins);
  h2_BTaggingEff_csv_tight_Num_udsg = new TH2D("h2_BTaggingEff_csv_tight_Num_udsg", "b-tagging effiency, Numerator, MC, CSV tight, udsg-jets, #eta vs p_{T};p_{T};#eta", nBins_pt, pt_bins, nBins_eta, eta_bins);


  // Finely Binned Histograms
  h2_BTaggingEff_csv_fineBinning_Denom_b = new TH2D("h2_BTaggingEff_csv_fineBinning_Denom_b", "b-tagging effiency, Denominator, MC, CSV, b-jets, fine binning, #eta vs p_{T};p_{T};#eta", nBins_pt_fine, pt_bins_fine, nBins_eta_fine, eta_bins_fine);
  h2_BTaggingEff_csv_fineBinning_Denom_c = new TH2D("h2_BTaggingEff_csv_fineBinning_Denom_c", "b-tagging effiency, Denominator, MC, CSV loose, c-jets, fine binning, #eta vs p_{T};p_{T};#eta", nBins_pt_fine, pt_bins_fine, nBins_eta_fine, eta_bins_fine);
  h2_BTaggingEff_csv_fineBinning_Denom_udsg = new TH2D("h2_BTaggingEff_csv_fineBinning_Denom_udsg", "b-tagging effiency, Denominator, MC, CSV loose, udsg-jets, fine binning, #eta vs p_{T};p_{T};#eta", nBins_pt_fine, pt_bins_fine, nBins_eta_fine, eta_bins_fine);

  h2_BTaggingEff_csv_fineBinning_loose_Num_b = new TH2D("h2_BTaggingEff_csv_fineBinning_loose_Num_b", "b-tagging effiency, Numerator, MC, CSV loose, b-jets, fine binning, #eta vs p_{T};p_{T};#eta", nBins_pt_fine, pt_bins_fine, nBins_eta_fine, eta_bins_fine);
  h2_BTaggingEff_csv_fineBinning_loose_Num_c = new TH2D("h2_BTaggingEff_csv_fineBinning_loose_Num_c", "b-tagging effiency, Numerator, MC, CSV loose, c-jets, fine binning, #eta vs p_{T};p_{T};#eta", nBins_pt_fine, pt_bins_fine, nBins_eta_fine, eta_bins_fine);
  h2_BTaggingEff_csv_fineBinning_loose_Num_udsg = new TH2D("h2_BTaggingEff_csv_fineBinning_loose_Num_udsg", "b-tagging effiency, Numerator, MC, CSV loose, udsg-jets, fine binning, #eta vs p_{T};p_{T};#eta", nBins_pt_fine, pt_bins_fine, nBins_eta_fine, eta_bins_fine);


  h2_BTaggingEff_csv_fineBinning_med_Num_b = new TH2D("h2_BTaggingEff_csv_fineBinning_med_Num_b", "b-tagging effiency, Numerator, MC, CSV med, b-jets, fine binning, #eta vs p_{T};p_{T};#eta", nBins_pt_fine, pt_bins_fine, nBins_eta_fine, eta_bins_fine);
  h2_BTaggingEff_csv_fineBinning_med_Num_c = new TH2D("h2_BTaggingEff_csv_fineBinning_med_Num_c", "b-tagging effiency, Numerator, MC, CSV med, c-jets, fine binning, #eta vs p_{T};p_{T};#eta", nBins_pt_fine, pt_bins_fine, nBins_eta_fine, eta_bins_fine);
  h2_BTaggingEff_csv_fineBinning_med_Num_udsg = new TH2D("h2_BTaggingEff_csv_fineBinning_med_Num_udsg", "b-tagging effiency, Numerator, MC, CSV med, udsg-jets, fine binning, #eta vs p_{T};p_{T};#eta", nBins_pt_fine, pt_bins_fine, nBins_eta_fine, eta_bins_fine);


  h2_BTaggingEff_csv_fineBinning_tight_Num_b = new TH2D("h2_BTaggingEff_csv_fineBinning_tight_Num_b", "b-tagging effiency, Numerator, MC, CSV tight, b-jets, fine binning, #eta vs p_{T};p_{T};#eta", nBins_pt_fine, pt_bins_fine, nBins_eta_fine, eta_bins_fine);
  h2_BTaggingEff_csv_fineBinning_tight_Num_c = new TH2D("h2_BTaggingEff_csv_fineBinning_tight_Num_c", "b-tagging effiency, Numerator, MC, CSV tight, c-jets, fine binning, #eta vs p_{T};p_{T};#eta", nBins_pt_fine, pt_bins_fine, nBins_eta_fine, eta_bins_fine);
  h2_BTaggingEff_csv_fineBinning_tight_Num_udsg = new TH2D("h2_BTaggingEff_csv_fineBinning_tight_Num_udsg", "b-tagging effiency, Numerator, MC, CSV tight, udsg-jets, fine binning, #eta vs p_{T};p_{T};#eta", nBins_pt_fine, pt_bins_fine, nBins_eta_fine, eta_bins_fine);



  h2_BTaggingEff_csv_Denom_b->SetDirectory(BTagEffFile);
  h2_BTaggingEff_csv_Denom_c->SetDirectory(BTagEffFile);
  h2_BTaggingEff_csv_Denom_udsg->SetDirectory(BTagEffFile);
    
  h2_BTaggingEff_csv_loose_Num_b->SetDirectory(BTagEffFile);
  h2_BTaggingEff_csv_loose_Num_c->SetDirectory(BTagEffFile);
  h2_BTaggingEff_csv_loose_Num_udsg->SetDirectory(BTagEffFile);
    

  h2_BTaggingEff_csv_med_Num_b->SetDirectory(BTagEffFile);
  h2_BTaggingEff_csv_med_Num_c->SetDirectory(BTagEffFile);
  h2_BTaggingEff_csv_med_Num_udsg->SetDirectory(BTagEffFile);
    
    
  h2_BTaggingEff_csv_tight_Num_b->SetDirectory(BTagEffFile);
  h2_BTaggingEff_csv_tight_Num_c->SetDirectory(BTagEffFile);
  h2_BTaggingEff_csv_tight_Num_udsg->SetDirectory(BTagEffFile);


  h2_BTaggingEff_csv_fineBinning_Denom_b->SetDirectory(BTagEffFile);
  h2_BTaggingEff_csv_fineBinning_Denom_c->SetDirectory(BTagEffFile);
  h2_BTaggingEff_csv_fineBinning_Denom_udsg->SetDirectory(BTagEffFile);
    
  h2_BTaggingEff_csv_fineBinning_loose_Num_b->SetDirectory(BTagEffFile);
  h2_BTaggingEff_csv_fineBinning_loose_Num_c->SetDirectory(BTagEffFile);
  h2_BTaggingEff_csv_fineBinning_loose_Num_udsg->SetDirectory(BTagEffFile);
    

  h2_BTaggingEff_csv_fineBinning_med_Num_b->SetDirectory(BTagEffFile);
  h2_BTaggingEff_csv_fineBinning_med_Num_c->SetDirectory(BTagEffFile);
  h2_BTaggingEff_csv_fineBinning_med_Num_udsg->SetDirectory(BTagEffFile);
    
    
  h2_BTaggingEff_csv_fineBinning_tight_Num_b->SetDirectory(BTagEffFile);
  h2_BTaggingEff_csv_fineBinning_tight_Num_c->SetDirectory(BTagEffFile);
  h2_BTaggingEff_csv_fineBinning_tight_Num_udsg->SetDirectory(BTagEffFile);

    
}




//================//
//                //
// Main function  //
//                //
//================//

int bTagEffMaker::looper(TChain* chain, char* output_name, int nEvents, char* path){

  //
  // Set output file path
  //
  bTagEffPath = path;
  
  //
  // Benchmark
  //
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");
  
  //
  //Set up loop over chain
  //
  unsigned int nEvents_processed = 0;
  unsigned int nEventsToDo = chain->GetEntries();

  if( nEvents >= 0 ) nEventsToDo = nEvents;
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;

  //
  // Make BTagEff Ntuple  
  //
  TH1::SetDefaultSumw2();
  
  MakeBTagEffNtuple( Form("bTagEfficiency__%s.root", output_name) );

  
  //
  // File Loop
  //
  while ( (currentFile = (TFile*)fileIter.Next()) ) { 

    //
    // Get File Content
    //
    if(nEvents_processed >= nEventsToDo) continue;
    TFile *file = new TFile( currentFile->GetTitle() );
    TTree *tree = (TTree*)file->Get("Events");
    cms3.Init(tree);
    cout << "file name is " << file->GetName() << endl;

    //
    // Loop over Events in current file
    //
    unsigned int nEventsTree = tree->GetEntriesFast();

    for(unsigned int evt = 0; evt < nEventsTree; evt++){

      //
      // Get Event Content
      //
      if(nEvents_processed >= nEventsToDo) break;
      cms3.GetEntry(evt);
      nEvents_processed++;

      //
      // Progress
      //
      CMS3::progress(nEvents_processed, nEventsToDo);

      //
      // Fill Histograms
      //
      for(size_t idx = 0; idx < pfjets_p4().size(); ++idx){
	
	double pt  = pfjets_p4().at(idx).Pt();
	double eta = pfjets_p4().at(idx).Eta();

	// Selection 
	if( pt < skim_jet_pt ) continue;
	if( fabs(eta) > skim_jet_eta ) continue;


	int flav   = pfjets_hadronFlavour().at(idx);
	
	double csv = getbtagvalue("pfCombinedInclusiveSecondaryVertexV2BJetTags", idx);
      

	// b-jets
	if( abs(flav) == 5 ){

	  h2_BTaggingEff_csv_Denom_b->Fill( std::min(pt,pt_max), std::min(fabs(eta),eta_max) );

	  h2_BTaggingEff_csv_fineBinning_Denom_b->Fill( std::min(pt,pt_max_fine), std::min(fabs(eta),eta_max_fine) );
	  
	  if( csv > csv_wp_loose ){
	    h2_BTaggingEff_csv_loose_Num_b->Fill( std::min(pt,pt_max), std::min(fabs(eta),eta_max) );
	    h2_BTaggingEff_csv_fineBinning_loose_Num_b->Fill( std::min(pt,pt_max_fine), std::min(fabs(eta),eta_max_fine) );
	  }
	  if( csv > csv_wp_med ){
	    h2_BTaggingEff_csv_med_Num_b->Fill( std::min(pt,pt_max), std::min(fabs(eta),eta_max) );
	    h2_BTaggingEff_csv_fineBinning_med_Num_b->Fill( std::min(pt,pt_max_fine), std::min(fabs(eta),eta_max_fine) );
	  }
	  if( csv > csv_wp_tight ){
	    h2_BTaggingEff_csv_tight_Num_b->Fill( std::min(pt,pt_max), std::min(fabs(eta),eta_max) );
	    h2_BTaggingEff_csv_fineBinning_tight_Num_b->Fill( std::min(pt,pt_max_fine), std::min(fabs(eta),eta_max_fine) );
	  }

	} // end if b-jet


	// c-jets
	if( abs(flav) == 4 ){

	  h2_BTaggingEff_csv_Denom_c->Fill( std::min(pt,pt_max), std::min(fabs(eta),eta_max) );
	  h2_BTaggingEff_csv_fineBinning_Denom_c->Fill( std::min(pt,pt_max_fine), std::min(fabs(eta),eta_max_fine) );
	  
	  if( csv > csv_wp_loose ){
	    h2_BTaggingEff_csv_loose_Num_c->Fill( std::min(pt,pt_max), std::min(fabs(eta),eta_max) );
	    h2_BTaggingEff_csv_fineBinning_loose_Num_c->Fill( std::min(pt,pt_max_fine), std::min(fabs(eta),eta_max_fine) );
	  }
	  if( csv > csv_wp_med ){
	    h2_BTaggingEff_csv_med_Num_c->Fill( std::min(pt,pt_max), std::min(fabs(eta),eta_max) );
	    h2_BTaggingEff_csv_fineBinning_med_Num_c->Fill( std::min(pt,pt_max_fine), std::min(fabs(eta),eta_max_fine) );
	  }
	  if( csv > csv_wp_tight ){
	    h2_BTaggingEff_csv_tight_Num_c->Fill( std::min(pt,pt_max), std::min(fabs(eta),eta_max) );
	    h2_BTaggingEff_csv_fineBinning_tight_Num_c->Fill( std::min(pt,pt_max_fine), std::min(fabs(eta),eta_max_fine) );
	  }

	} // end if c-jet

	// udsg-jets
	if( abs(flav) == 3 ||
	    abs(flav) == 2 || 
	    abs(flav) == 1 ||
	    abs(flav) == 0 ||
	    abs(flav) == 21   ){

	  h2_BTaggingEff_csv_Denom_udsg->Fill( std::min(pt,pt_max), std::min(fabs(eta),eta_max) );
	  h2_BTaggingEff_csv_fineBinning_Denom_udsg->Fill( std::min(pt,pt_max_fine), std::min(fabs(eta),eta_max_fine) );
	  
	  if( csv > csv_wp_loose ){
	    h2_BTaggingEff_csv_loose_Num_udsg->Fill( std::min(pt,pt_max), std::min(fabs(eta),eta_max) );
	    h2_BTaggingEff_csv_fineBinning_loose_Num_udsg->Fill( std::min(pt,pt_max_fine), std::min(fabs(eta),eta_max_fine) );
	  }
	  if( csv > csv_wp_med ){
	    h2_BTaggingEff_csv_med_Num_udsg->Fill( std::min(pt,pt_max), std::min(fabs(eta),eta_max) );
	    h2_BTaggingEff_csv_fineBinning_med_Num_udsg->Fill( std::min(pt,pt_max_fine), std::min(fabs(eta),eta_max_fine) );
	  }
	  if( csv > csv_wp_tight ){
	    h2_BTaggingEff_csv_tight_Num_udsg->Fill( std::min(pt,pt_max), std::min(fabs(eta),eta_max) );
	    h2_BTaggingEff_csv_fineBinning_tight_Num_udsg->Fill( std::min(pt,pt_max_fine), std::min(fabs(eta),eta_max_fine) );
	  }

	} // end if udsg-jet



      } // end loop over jets
          
    
    }//close event loop
    

    //
    // Close input file
    //
    file->Close();
    delete file;

  }//close file loop


  //
  // Write and Close baby file
  //
  BTagEffFile->cd();
  BTagEffFile->Write();
  BTagEffFile->Close();


  //
  // Benchmarking
  //
  bmark->Stop("benchmark");
  

  //
  // Print Skim Cutflow
  //
  cout << endl;
  cout << "Wrote babies into file " << BTagEffFile->GetName() << endl;
  cout << "-----------------------------" << endl;
  cout << "Events Processed                     " << nEvents_processed << endl;
    cout << "-----------------------------" << endl;
  cout << "CPU  Time:   " << Form( "%.01f", bmark->GetCpuTime("benchmark")  ) << endl;                                                                                          
  cout << "Real Time:   " << Form( "%.01f", bmark->GetRealTime("benchmark") ) << endl;
  cout << endl;
  delete bmark;

  return 0;  

}
