#include "TFile.h"
#include "TString.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TStyle.h"
#include <vector>

void dividePlots(TString infile = "bTagEfficiency__ttbar_powheg_pythia8_25ns_1.root", TString outfile = "btageff__ttbar_powheg_pythia8_25ns.root") {

  // Setup
  TH1::SetDefaultSumw2();
  gStyle->SetPaintTextFormat("0.2f");

  // Open input file
  TFile* fin = new TFile(infile);

  // Open output file
  TFile* fout = new TFile(outfile,"RECREATE");
  fout->cd();

  // Vector of histogram names
  std::vector<TString> hist_names;
  hist_names.push_back("h2_BTaggingEff_csv_loose_Num_b");
  hist_names.push_back("h2_BTaggingEff_csv_loose_Num_c");
  hist_names.push_back("h2_BTaggingEff_csv_loose_Num_udsg");
    
  hist_names.push_back("h2_BTaggingEff_csv_med_Num_b");
  hist_names.push_back("h2_BTaggingEff_csv_med_Num_c");
  hist_names.push_back("h2_BTaggingEff_csv_med_Num_udsg");
    
  hist_names.push_back("h2_BTaggingEff_csv_tight_Num_b");
  hist_names.push_back("h2_BTaggingEff_csv_tight_Num_c");
  hist_names.push_back("h2_BTaggingEff_csv_tight_Num_udsg");


  // Rebinning Histgrams:
  bool doRebin=true;

  double eps = 0.000001;

  // Set pT bins
  int Pt_nBins = 17;
  double *Pt_bins = new double[Pt_nBins+1]{20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 120.0, 150.0, 200.0, 300.0, 400.0, 600.0+eps};

  // Set eta bins
  int Eta_nBins = 7;
  double *Eta_bins = new double[Eta_nBins+1]{0.0, 0.4, 0.8, 1.2, 1.6, 2.0, 2.4, 2.8+eps};

  
  // Loop over histograms and calculate efficiencies
  for (unsigned int i = 0; i<hist_names.size(); ++i) {

    // numerator name
    TString name_num = hist_names.at(i);

    // denominator name
    TString name_denom(name_num);
    name_denom.ReplaceAll("_Num","_Denom");

    // remove working point from denominator name
    name_denom.ReplaceAll("_loose","");
    name_denom.ReplaceAll("_med","");
    name_denom.ReplaceAll("_tight","");

    // get numerator and denominator
    TH2D* h2_num = (TH2D*) fin->Get(name_num);
    TH2D* h2_denom = (TH2D*) fin->Get(name_denom);
    
    // efficiency name
    TString name_eff(name_num);
    name_eff.ReplaceAll("_Num","_Eff");

    // clone numerator histogram and divide by denominator
    TH2D* h2_eff = (TH2D*) h2_num->Clone(name_eff);
    h2_eff->SetDirectory(fout);      
    h2_eff->Divide(h2_num,h2_denom,1,1,"B");

    // set efficiency histogram title
    TString title_eff = (TString)h2_eff->GetTitle();
    title_eff.ReplaceAll("Numerator, ", "");
    h2_eff->SetTitle(title_eff);
 
  } // end loop over nominal histograms


  // Repeat for finely binned histograms
  for (unsigned int i = 0; i<hist_names.size(); ++i) {

    // numerator name
    TString name_num = hist_names.at(i);
    name_num.ReplaceAll("_csv", "_csv_fineBinning");

    // denominator name
    TString name_denom(name_num);
    name_denom.ReplaceAll("_Num","_Denom");

    // remove working point from denominator name
    name_denom.ReplaceAll("_loose","");
    name_denom.ReplaceAll("_med","");
    name_denom.ReplaceAll("_tight","");

    // get numerator and denominator
    TH2D* h2_num = (TH2D*) fin->Get(name_num);
    TH2D* h2_denom = (TH2D*) fin->Get(name_denom);
    
    // efficiency name
    TString name_eff(name_num);
    name_eff.ReplaceAll("_Num","_Eff");

    // clone numerator histogram and divide by denominator
    TH2D* h2_eff = (TH2D*) h2_num->Clone(name_eff);
    h2_eff->SetDirectory(fout);      
    h2_eff->Divide(h2_num,h2_denom,1,1,"B");

    // set efficiency histogram title
    TString title_eff = (TString)h2_eff->GetTitle();
    title_eff.ReplaceAll("Numerator, ", "");
    h2_eff->SetTitle(title_eff);
 
  } // end loop over finely binned histograms


  // Repeat for finely binned histograms, rebinning as necessary
  if(doRebin){

    for (unsigned int i = 0; i<hist_names.size(); ++i) {

      // numerator name
      TString name_num = hist_names.at(i);
      name_num.ReplaceAll("_csv", "_csv_fineBinning");

      // denominator name
      TString name_denom(name_num);
      name_denom.ReplaceAll("_Num","_Denom");

      // remove working point from denominator name
      name_denom.ReplaceAll("_loose","");
      name_denom.ReplaceAll("_med","");
      name_denom.ReplaceAll("_tight","");

      // get numerator and denominator
      TH2D* h2_num = (TH2D*) fin->Get(name_num);
      TH2D* h2_denom = (TH2D*) fin->Get(name_denom);

      // declare new histograms that are rebinned in Pt and Eta
      TString num_rebin_name = (TString)h2_num->GetName();
      num_rebin_name.ReplaceAll("_Num", "_Num_rebin");
      TString num_rebin_title = (TString)h2_num->GetTitle();
      num_rebin_name.ReplaceAll("fine binning, ", "rebinned, "); 
      TH2D* h2_num_rebin = new TH2D(num_rebin_name, num_rebin_title, Pt_nBins, Pt_bins, Eta_nBins, Eta_bins);

      TString denom_rebin_name = (TString)h2_denom->GetName();
      denom_rebin_name.ReplaceAll("_Denom", "_Denom_rebin");
      TString denom_rebin_title = (TString)h2_denom->GetTitle();
      denom_rebin_title.ReplaceAll("fine binning, ", "rebinned, ");
      TH2D* h2_denom_rebin = new TH2D(denom_rebin_name, denom_rebin_title, Pt_nBins, Pt_bins, Eta_nBins, Eta_bins);


      // Fill rebinned numerator and denominator
      for(int iBinX=1; iBinX<(int)h2_num->GetNbinsX()+1; iBinX++){
	for(int iBinY=1; iBinY<(int)h2_num->GetNbinsY()+1; iBinY++){
	  h2_num_rebin->Fill( h2_num->GetXaxis()->GetBinCenter(iBinX), h2_num->GetYaxis()->GetBinCenter(iBinY), h2_num->GetBinContent(iBinX,iBinY) );
	  h2_denom_rebin->Fill( h2_denom->GetXaxis()->GetBinCenter(iBinX), h2_denom->GetYaxis()->GetBinCenter(iBinY), h2_denom->GetBinContent(iBinX,iBinY) );
	}
      }
    
   
      // efficiency name
      TString name_eff(name_num);
      name_eff.ReplaceAll("fineBinning","rebin");
      name_eff.ReplaceAll("_Num","_Eff");
      
      TH2D* h2_eff = (TH2D*) h2_num_rebin->Clone(name_eff);
      h2_eff->SetDirectory(fout);      
      h2_eff->Divide(h2_num_rebin,h2_denom_rebin,1,1,"B");
    
      TString title_eff = (TString)h2_eff->GetTitle();
      title_eff.ReplaceAll("Numerator, ", "");
      title_eff.ReplaceAll("fine binning, ", "rebinned, ");
      h2_eff->SetTitle(title_eff);
 

      // Clean up
      h2_num_rebin->~TH2D();
      h2_denom_rebin->~TH2D();    

    } // end loop over fine histograms, to rebin

  } // end if doRebin
    
  fin->Close();
  fout->Write();
  fout->Close();

  return;
}  
