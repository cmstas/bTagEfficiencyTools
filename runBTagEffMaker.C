#include "looper.h"
#include "TChain.h"
#include "TString.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;


vector<TString> load(char *type, const char *filename, char *input){
  
  vector<TString> output;
  char buffer[500];
  char StringValue[1000];
  ifstream IN(input);
  while( IN.getline(buffer, 500, '\n') ){
    // ok = false;
    if (buffer[0] == '#') {
      continue; // Skip lines commented with '#'
    }
    if( !strcmp(buffer, "SAMPLE")){
      bool add = false;
      IN.getline(buffer, 500, '\n');
      sscanf(buffer, "Name\t%s", StringValue);
      if((string)StringValue==(string)type) add=true;
      IN.getline(buffer, 500, '\n');
      sscanf(buffer, "Path\t%s", StringValue);
      if(add){
	std::ostringstream addStream;
	addStream << StringValue << filename;
	TString addString = addStream.str().c_str();
	output.push_back(addString);
      }
    }
  }
  return output;
}
  

int main(int argc, char **argv){
  
  //
  // Input sanitation
  //
  if(argc<2){
    cout<<" runBTagEffMaker takes five arguments: ./runBTagEffMaker sample_name nevents file_number outpath samplelist" << endl;
    cout<<" Need to provide at least sample_name; nevents=-1 (-1=all events), file_number=-1 (-1=merged_ntuple_*.root), output=/nfs-7/userdata/stopRun2/  samplelist=sample.dat by default"<<endl;
    return 0;
  }

  bool verbose = false;

  //
  // Initialize looper
  //
  bTagEffMaker *mylooper = new bTagEffMaker();


  //
  // Skim Parameters 
  //
  double eps = 0.00001;

  // Cuts on jet kinematics
  double jet_pt  = 10.0;
  double jet_eta = 2.8;


  // CSV Working Points
  double csv_loose = 0.605;
  double csv_med   = 0.890;
  double csv_tight = 0.970;


  // Pt Binning for Nominal Histograms
  const int Pt_nBins = 17;
  double Pt_min      = 20.0;
  double Pt_max      = 600.0;
  double *Pt_bins    = new double[Pt_nBins+1]{20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 120.0, 150.0, 200.0, 300.0, 400.0, 600.0+eps};

  if(verbose) cout << "  PT bin edges for nominal histograms: " << endl;
  for(int iBin=0; iBin<Pt_nBins+1; iBin++){
    if(verbose) cout << "    Pt_bins[" << iBin << "]=" << Pt_bins[iBin] << endl;
  }
  if(verbose) cout << endl;


  // Eta Binning for Nominal Histograms
  const int Eta_nBins = 7;
  double Eta_min      = 0.0;
  double Eta_max      = 2.8;
  double *Eta_bins    = new double[Eta_nBins+1];

  if(verbose) cout << "  ETA bin edges for nominal histograms: " << endl;
  for(int iBin=0; iBin<Eta_nBins+1; iBin++){
    Eta_bins[iBin] = (iBin)*(Eta_max-Eta_min)/Eta_nBins;
    if(iBin==Eta_nBins) Eta_bins[iBin] += eps;
    if(verbose) cout << "    Eta_bins[" << iBin << "]=" << Eta_bins[iBin] << endl;
  }
  if(verbose) cout << endl;


  // Pt Binning for Finely Binned Histograms
  const int Pt_nBins_fine = 120;
  double Pt_min_fine      = 0.0;
  double Pt_max_fine      = 600.0;
  double *Pt_bins_fine    = new double[Pt_nBins_fine+1];

  if(verbose) cout << "  PT bin edges for fine histograms: " << endl;
  for(int iBin=0; iBin<Pt_nBins_fine+1; iBin++){
    Pt_bins_fine[iBin] = (iBin)*(Pt_max_fine-Pt_min_fine)/Pt_nBins_fine;
    if(iBin==Pt_nBins_fine) Pt_bins_fine[iBin] += eps;
    if(verbose) cout << "    Pt_bins_fine[" << iBin << "]=" << Pt_bins_fine[iBin] << endl;
  }
  if(verbose) cout << endl;

  
  // Eta Binning for Finely Binned Histograms
  const int Eta_nBins_fine = 28;
  double Eta_min_fine      = 0.0;
  double Eta_max_fine      = 2.8;
  double *Eta_bins_fine    = new double[Eta_nBins_fine+1];

  if(verbose) cout << "  ETA bin edges for fine histograms: " << endl;
  for(int iBin=0; iBin<Eta_nBins_fine+1; iBin++){
    Eta_bins_fine[iBin] = (iBin)*(Eta_max_fine-Eta_min_fine)/Eta_nBins_fine;
    if(iBin==Eta_nBins_fine) Eta_bins_fine[iBin] += eps;
    if(verbose) cout << "    Eta_bins_fine[" << iBin << "]=" << Eta_bins_fine[iBin] << endl;
  }
  if(verbose) cout << endl;
  
  
  //
  // Set Skim Variables
  //
  mylooper->setSkimVariables(jet_pt, jet_eta, csv_loose, csv_med, csv_tight, Pt_nBins, Pt_min, Pt_max, Pt_bins, Eta_nBins, Eta_min, Eta_max, Eta_bins, Pt_nBins_fine, Pt_min_fine, Pt_max_fine, Pt_bins_fine, Eta_nBins_fine, Eta_min_fine, Eta_max_fine, Eta_bins_fine);


  //
  // Use arguments to set run parameters
  //
  int nevents = -1;
  if(argc>2) nevents = atoi(argv[2]);  
  
  int file=-1;
  if(argc>3) file = atoi(argv[3]);

  char* dirpath = ".";  
  if(argc>4) dirpath = argv[4];

  const char* filename = (file == -1 ? "merged_ntuple_*.root" : Form("merged_ntuple_%i.root", file));
  
  const char* suffix = file == -1 ? "" : Form("_%i", file);

  char *input = "sample.dat";
  if(argc>5) input = argv[5];


  //
  // Intialize TChain, load samples
  //
  TChain *sample = new TChain("Events");
  vector<TString> samplelist = load(argv[1], filename, input);//new
  for(unsigned int i = 0; i<samplelist.size(); ++i){
    cout << "Add sample " << samplelist[i] << " to files to be processed." << endl;
    sample->Add(samplelist[i].Data());
  }


  //
  // Run Looper
  //
  mylooper->looper(sample, Form("%s%s", argv[1],suffix), nevents, dirpath);


  //
  // Return
  //
  return 0;
}
