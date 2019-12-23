///Author: Oleksii Poleshchuk
///
///KU Leuven 2016-2019
///
///Part of ScintillatorSim
///
/// \file ScintillatorSimEnergyScanTotalNoResAnalysis.C
///This script is used for automatic sorting of the Histograms produced
///with SpecMATscint.
///

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ofstream myfile;

void convertRoot(TString in_fname, float energyMeV, float energykeV, int nrebin) {

  TFile *f = new TFile(Form("%s.root",in_fname.Data()),"READ");
  if (f->IsZombie()) {
	  printf("ERROR opening FILE %s.root \n", in_fname.Data());
	  return -1;
  }

  TH1D *h1 = 0;

  f->GetObject("histograms/TotalNoRes", h1);

  double max1 = h1->GetMaximum();

  double nbins1 = h1->GetNbinsX();

  double bincenter1 = 0;

  double bincontent1 = 0;

  double counter1=h1->GetBinContent(energykeV)+h1->GetBinContent(energykeV+1);

  myfile<<energyMeV<<" "<<counter1<<endl;
  cout<<energyMeV<<" "<<counter1<<endl;
}

void ScintSimEnergyScanTotalNoResAnalysis(){
  myfile.open ("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_Escan.txt");
  myfile<<"Energy "<<"PeakNoResCounts"<<endl;
  cout<<"Energy "<<"PeakNoResCounts"<<endl;

  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.02MeV", 0.02, 20,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.03MeV", 0.03, 30,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.04MeV", 0.04, 40,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.05MeV", 0.05, 50,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.06MeV", 0.06, 60,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.07MeV", 0.07, 70,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.08MeV", 0.08, 80,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.09MeV", 0.09, 90,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.1MeV", 0.1, 100,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.11MeV", 0.11, 110,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.12MeV", 0.12, 120,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.13MeV", 0.13, 130,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.14MeV", 0.14, 140,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.15MeV", 0.15, 150,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.16MeV", 0.16, 160,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.17MeV", 0.17, 170,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.18MeV", 0.18, 180,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.19MeV", 0.19, 190,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.2MeV", 0.2, 200,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.21MeV", 0.21, 210,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.22MeV", 0.22, 220,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.23MeV", 0.23, 230,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.24MeV", 0.24, 240,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.25MeV", 0.25, 250,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.26MeV", 0.26, 260,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.27MeV", 0.27, 270,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.28MeV", 0.28, 280,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.29MeV", 0.29, 290,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.3MeV", 0.3, 300,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.4MeV", 0.4, 400,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.5MeV", 0.5, 500,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.6MeV", 0.6, 600,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.7MeV", 0.7, 700,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.8MeV", 0.8, 800,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E0.9MeV", 0.9, 900,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E1MeV", 1, 1000,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E1.1MeV", 1.1, 1100,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E1.2MeV", 1.2, 1200,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E1.3MeV", 1.3, 1300,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E1.4MeV", 1.4, 1400,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E1.5MeV", 1.5, 1500,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E1.6MeV", 1.6, 1600,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E1.7MeV", 1.7, 1700,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E1.8MeV", 1.8, 1800,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E1.9MeV", 1.9, 1900,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E2MeV", 2, 2000,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E3MeV", 3, 3000,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E4MeV", 4, 4000,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E5MeV", 5, 5000,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E6MeV", 6, 6000,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E7MeV", 7, 7000,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E8MeV", 8, 8000,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E9MeV", 9, 9000,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E10MeV", 10, 10000,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E11MeV", 11, 11000,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E12MeV", 12, 12000,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E13MeV", 13, 13000,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E14MeV", 14, 14000,1);
  convertRoot("CeBr3_box_24mmx24mmx24mm_131.25mm_3000000evnt_E15MeV", 15, 15000,1);

  myfile.close();
  printf("The data was saved\n");
  printf("DONE\n");
}
