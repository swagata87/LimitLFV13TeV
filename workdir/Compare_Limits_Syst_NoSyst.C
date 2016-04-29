#include "TSystem.h"
#include "TString.h"
#include "TEnv.h"
#include "TH1.h"
#include "TH1F.h"
#include "TGraphErrors.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TVectorD.h"
#include "TLine.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TMath.h"
#include "TSpline.h"
#include <algorithm>
#include "TGraphAsymmErrors.h"
#include "/user/mukherjee/limits_LFV/scripts/Environment.h"
#include "TLatex.h"

using namespace std;
using namespace TMath;

void Compare_Limits_Syst_NoSyst(TString in_dir)
{

  Char_t mass_dir_withSyst[200];
  Char_t mass_dir_noSyst[200];

  Char_t file_title[200];

  int mass_min=200;
  //  int mass_inter_0=400;  
  //  int mass_inter_1=600;
  int mass_max=400;

  int binning_0=200;
  //  int binning_1=200;
  // int binning_2=200;

  int mass=mass_min;

  TFile* outfile=new TFile("RPV_SystCompare.root","recreate");

  double expected_withSyst[200];
  //  double observed_withSyst[200]; 
  double expected_noSyst[200];
  // double observed_noSyst[200];
  //  double expected_withSyst_68_up[200];
  //  double expected_withSyst_68_down[200];
  double expected_withSyst_95_up[200];
  double expected_withSyst_95_down[200];  
  double xs_expected_withSyst[200];
  // double xs_observed_withSyst[200];  
  double expected_noSyst_95_up[200];
  double expected_noSyst_95_down[200];
  double xs_expected_noSyst[200];
  //  double xs_observed_noSyst[200];
  //  double xs_expected_withSyst_68_up[200];
  //  double xs_expected_withSyst_68_down[200];   
  double xs_expected_withSyst_95_up[200];
  double xs_expected_withSyst_95_down[200];  
  double xs_expected_noSyst_95_up[200];
  double xs_expected_noSyst_95_down[200];

  double masses[200];
  double xsec_NLO[200];
  double xsec_NLO_2[200];
  double xsec_NLO_3[200];

  for(int k=0; k<200; k++)
    {
      expected_withSyst[k]=0.;
      //observed_withSyst[k]=0.;
      expected_noSyst[k]=0.;
      //observed_noSyst[k]=0.;
      //  expected_withSyst_68_up[k]=0.;
      //  expected_withSyst_68_down[k]=0.;
      expected_withSyst_95_up[k]=0.;
      expected_withSyst_95_down[k]=0.;  
      expected_noSyst_95_up[k]=0.;
      expected_noSyst_95_down[k]=0.;
      masses[k]=0.; 
      //xsec[k]=0.;
      xsec_NLO[k]=0.;
      xs_expected_withSyst[k]=0.;
      //xs_observed_withSyst[k]=0.;  
      xs_expected_noSyst[k]=0.;
      //xs_observed_noSyst[k]=0.;
      //   xs_expected_withSyst_68_up[k]=0.;
      //   xs_expected_withSyst_68_down[k]=0.;   
      xs_expected_withSyst_95_up[k]=0.;
      xs_expected_withSyst_95_down[k]=0.;  
      xs_expected_noSyst_95_up[k]=0.;
      xs_expected_noSyst_95_down[k]=0.;
    }

  int counter_masses=0;

  while(mass<=mass_max)
    {
      masses[counter_masses]=mass;
      sprintf(file_title,"LQD_01_LLE_01_MSnl_scale_down_%d",(int)mass);
      get_environment(file_title);
      xsec_NLO[counter_masses]=BGcrosssection*BGweight;
      sprintf(mass_dir_withSyst,"/output_masses/Mass_%i_output",mass);   
      sprintf(mass_dir_noSyst,"/output_masses_WithoutTopSyst_MoreToy/Mass_%i_output",mass);
      TString basedir="/user/mukherjee/limits_LFV/scripts/";
      TString *massdir_withSyst=new TString(mass_dir_withSyst);
      TString *massdir_noSyst=new TString(mass_dir_noSyst);

      TString filename_withSyst=basedir+in_dir+*massdir_withSyst+"/condor/expected.root";
      //    TString filename_observed_withSyst = basedir+in_dir+*massdir_withSyst+"/condor/observed.root";

      TString filename_noSyst=basedir+in_dir+*massdir_noSyst+"/condor/expected.root";
      //TString filename_observed_noSyst = basedir+in_dir+*massdir_noSyst+"/condor/observed.root";

      double limit;

      TFile *expected_withSyst_file=new TFile(filename_withSyst);
      //TFile *observed_withSyst_file=new TFile(filename_observed_withSyst);      
      TTree *tree_withSyst = (TTree*)expected_withSyst_file->Get("limit");
      tree_withSyst->ResetBranchAddresses();
      tree_withSyst->SetBranchAddress("limit",&limit);
      int nrEntries_withSyst = tree_withSyst->GetEntries();
      double limits_withSyst[10000];
      for(int entryNr=0;entryNr<nrEntries_withSyst;entryNr++){
	tree_withSyst->GetEntry(entryNr);
	limits_withSyst[entryNr]=limit;
      }
      tree_withSyst->ResetBranchAddresses();
      std::sort(limits_withSyst, limits_withSyst + nrEntries_withSyst);


      TFile *expected_noSyst_file=new TFile(filename_noSyst);
      // TFile *observed_noSyst_file=new TFile(filename_observed_noSyst);
      TTree *tree_noSyst = (TTree*)expected_noSyst_file->Get("limit");
      tree_noSyst->ResetBranchAddresses();
      tree_noSyst->SetBranchAddress("limit",&limit);
      int nrEntries_noSyst = tree_noSyst->GetEntries();
      double limits_noSyst[10000];
      for(int entryNr=0;entryNr<nrEntries_noSyst;entryNr++){
        tree_noSyst->GetEntry(entryNr);
        limits_noSyst[entryNr]=limit;
      }
      tree_noSyst->ResetBranchAddresses();
      std::sort(limits_noSyst, limits_noSyst + nrEntries_noSyst);
     
      expected_withSyst[counter_masses]=limits_withSyst[Nint(nrEntries_withSyst*0.5)];
      expected_noSyst[counter_masses]=limits_noSyst[Nint(nrEntries_noSyst*0.5)];
      //expected_withSyst_68_up[counter_masses]=limits_withSyst[Nint(nrEntries_withSyst*0.841344746)];
      //expected_withSyst_68_down[counter_masses]=limits_withSyst[Nint(nrEntries_withSyst*0.158655254)];      
      expected_withSyst_95_up[counter_masses]=limits_withSyst[Nint(nrEntries_withSyst*0.977249868)];
      expected_noSyst_95_up[counter_masses]=limits_noSyst[Nint(nrEntries_noSyst*0.977249868)];
      expected_withSyst_95_down[counter_masses]=limits_withSyst[Nint(nrEntries_withSyst*0.022750132)];           
      expected_noSyst_95_down[counter_masses]=limits_noSyst[Nint(nrEntries_noSyst*0.022750132)];

      delete tree_withSyst;
      delete expected_withSyst_file;
      delete massdir_withSyst;
      
      delete tree_noSyst;
      delete expected_noSyst_file;
      delete massdir_noSyst;

      //TTree *tree_observed_withSyst = (TTree*)observed_withSyst_file->Get("limit");
      //tree_observed_withSyst->ResetBranchAddresses();
      // tree_observed_withSyst->SetBranchAddress("limit",&limit);      
      // nrEntries_withSyst = tree_observed_withSyst->GetEntries();
      //   for(int entryNr=0;entryNr<nrEntries_withSyst;entryNr++){
      //	tree_observed_withSyst->GetEntry(entryNr);
      //}
      //observed_withSyst[counter_masses]=limit;

      /*
      TTree *tree_observed_noSyst = (TTree*)observed_noSyst_file->Get("limit");
      tree_observed_noSyst->ResetBranchAddresses();
      tree_observed_noSyst->SetBranchAddress("limit",&limit);
      nrEntries_noSyst = tree_observed_noSyst->GetEntries();
      for(int entryNr=0;entryNr<nrEntries_noSyst;entryNr++){
        tree_observed_noSyst->GetEntry(entryNr);
      }
      observed_noSyst[counter_masses]=limit;
      */

      xs_expected_withSyst[counter_masses]=expected_withSyst[counter_masses]*xsec_NLO[counter_masses]; ///Aeff[counter_masses];
      xs_expected_noSyst[counter_masses]=expected_noSyst[counter_masses]*xsec_NLO[counter_masses]; ///Aeff[counter_masses];
                                                    
      //xs_observed_withSyst[counter_masses]=observed_withSyst[counter_masses]*xsec_NLO[counter_masses]; ///Aeff[counter_masses];
      //xs_observed_noSyst[counter_masses]=observed_noSyst[counter_masses]*xsec_NLO[counter_masses];

      //  xs_expected_withSyst_68_up[counter_masses]=expected_withSyst_68_up[counter_masses]*xsec_NLO[counter_masses];
      //  xs_expected_withSyst_68_down[counter_masses]=expected_withSyst_68_down[counter_masses]*xsec_NLO[counter_masses];   
      xs_expected_withSyst_95_up[counter_masses]=expected_withSyst_95_up[counter_masses]*xsec_NLO[counter_masses];
      xs_expected_noSyst_95_up[counter_masses]=expected_noSyst_95_up[counter_masses]*xsec_NLO[counter_masses];

      xs_expected_withSyst_95_down[counter_masses]=expected_withSyst_95_down[counter_masses]*xsec_NLO[counter_masses]; 
      xs_expected_noSyst_95_down[counter_masses]=expected_noSyst_95_down[counter_masses]*xsec_NLO[counter_masses];

      //cout << "expected_withSyst     expected_noSyst       observed_withSyst     observed_noSyst " << std::endl;
      cout << mass << "  &  With syst : " << xs_expected_withSyst[counter_masses] << "  &  Without systematic : "   << xs_expected_noSyst[counter_masses]    << endl;

      counter_masses++;

      

      //if(mass<mass_inter_0){
      mass+=binning_0; //}
      //      else { // mass+=binning_1;
      //	if(mass<mass_inter_1) mass+=binning_1;
      //	else mass+=binning_2;
      //}
    }

  std::cout << "limits have been written, now produce the corresponding plots" << std::endl;

  /*
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.15);  
  gStyle->SetPadTopMargin(0.05);   
  gStyle->SetTitleXSize(0.05);
  gStyle->SetTitleXOffset(1.05);
  gStyle->SetTitleYSize(0.05);
  gStyle->SetTitleYOffset(1.05);
  */
      
  //cross section limit
  TCanvas* total = new TCanvas("total","total",800,800);
  total->cd();
  total->SetLogy();
  /*
  TGraph *graph_observed_withSyst_total = new TGraph(counter_masses,masses,xs_observed_withSyst);
  graph_observed_withSyst_total->GetXaxis()->SetRangeUser(mass_min,mass_max);
  graph_observed_withSyst_total->GetYaxis()->SetRangeUser(0.1,1000.);
  graph_observed_withSyst_total->SetTitle("");
  graph_observed_withSyst_total->SetMarkerStyle(20);
  graph_observed_withSyst_total->SetMarkerSize(1.4);
  graph_observed_withSyst_total->SetMarkerColor(kRed);
  graph_observed_withSyst_total->SetLineColor(kRed);
  graph_observed_withSyst_total->SetLineWidth(3);   
  graph_observed_withSyst_total->GetXaxis()->SetTitle("M_{#tilde{#nu_{#tau}}} (GeV)");
  graph_observed_withSyst_total->GetYaxis()->SetTitle("#sigma^{prod}_{#tilde{#nu_{#tau}}} #times BR ( #tilde{#nu_{#tau}} #rightarrow e#mu ) (fb)");
  graph_observed_withSyst_total->Draw("Apl");  
  */

  TGraph *graph_expected_withSyst_total = new TGraph(counter_masses,masses,xs_expected_withSyst);
  graph_expected_withSyst_total->GetXaxis()->SetRangeUser(mass_min,mass_max);
  graph_expected_withSyst_total->GetYaxis()->SetRangeUser(0.1,1000.);
  graph_expected_withSyst_total->SetTitle("");
  graph_expected_withSyst_total->SetMarkerStyle(20);
  graph_expected_withSyst_total->SetMarkerColor(kRed);
  graph_expected_withSyst_total->SetLineColor(kRed);
  graph_expected_withSyst_total->SetLineWidth(2);
  graph_expected_withSyst_total->SetLineStyle(2);    
  graph_expected_withSyst_total->GetXaxis()->SetTitle("M_{#tilde{#nu_{#tau}}} (GeV)");
  graph_expected_withSyst_total->GetYaxis()->SetTitle("#sigma^{prod}_{#tilde{#nu_{#tau}}} #times BR ( #tilde{#nu_{#tau}} #rightarrow e#mu ) (fb)");
  graph_expected_withSyst_total->Draw("Apl");  
  
  //  TGraph *graph_expected_withSyst_68_up_total = new TGraph(counter_masses,masses,xs_expected_withSyst_68_up);    
  // TGraph *graph_expected_withSyst_68_down_total = new TGraph(counter_masses,masses,xs_expected_withSyst_68_down);    
  TGraph *grshade_95_total = new TGraph(2*counter_masses);
  for (int i=0;i<counter_masses;i++) {
    grshade_95_total->SetPoint(i,masses[i],xs_expected_withSyst_95_up[i]);
    grshade_95_total->SetPoint(counter_masses+i,masses[counter_masses-i-1],xs_expected_withSyst_95_down[counter_masses-i-1]);
  }
  
  grshade_95_total->SetFillStyle(3004);
  //  grshade_95_total->SetFillColor(kRed);
  grshade_95_total->SetFillColorAlpha(kRed, 0.35);
  //grshade_95_total->Draw("f");
  
  //  TGraph *grshade_68_total = new TGraph(2*counter_masses);
  // for (int i=0;i<counter_masses;i++) {
  //  grshade_68_total->SetPoint(i,masses[i],xs_expected_withSyst_68_up[i]);
  // grshade_68_total->SetPoint(counter_masses+i,masses[counter_masses-i-1],xs_expected_withSyst_68_down[counter_masses-i-1]);
  // }
  
  //grshade_68_total->SetFillStyle(3005);
  //grshade_68_total->SetFillColor(kGreen+3);
  //grshade_68_total->Draw("f");

  graph_expected_withSyst_total->Draw("pl,same");  
  //graph_observed_withSyst_total->Draw("pl,same");

  std::cout<< "Prepare to draw graph 1" << std::endl;
  
  TGraph *graph_xsec= new TGraph(counter_masses,masses,xsec_NLO);
  graph_xsec->SetTitle("");
  graph_xsec->SetMarkerStyle(0);
  graph_xsec->SetMarkerSize(1.4);
  graph_xsec->SetMarkerColor(kBlue);
  graph_xsec->SetLineColor(kBlue);
  graph_xsec->SetLineWidth(2);    
  graph_xsec->GetXaxis()->SetTitle("M_{#tilde{#nu_{#tau}}} [TeV]");
  graph_xsec->GetYaxis()->SetTitle("95%CL #sigma_{sig}xBR / fb");   
  graph_xsec->Draw("pl,same");
  std::cout << graph_xsec << std::endl;
  TSpline3 *s3 = new TSpline3("s3",graph_xsec->GetX(),graph_xsec->GetY(),graph_xsec->GetN());
  s3->SetLineColor(kRed);
  std::cout<< "Prepare to draw legend" << std::endl;

  // No syst
  /*
  TGraph *graph_observed_noSyst_total = new TGraph(counter_masses,masses,xs_observed_noSyst);
  graph_observed_noSyst_total->GetXaxis()->SetRangeUser(mass_min,mass_max);
  graph_observed_noSyst_total->GetYaxis()->SetRangeUser(0.1,1000.);
  graph_observed_noSyst_total->SetTitle("");
  graph_observed_noSyst_total->SetMarkerStyle(20);
  graph_observed_noSyst_total->SetMarkerSize(1.4);
  graph_observed_noSyst_total->SetMarkerColor(kGreen);
  graph_observed_noSyst_total->SetLineColor(kGreen);
  graph_observed_noSyst_total->SetLineWidth(3);   
  graph_observed_noSyst_total->GetXaxis()->SetTitle("M_{#tilde{#nu_{#tau}}} (GeV)");
  graph_observed_noSyst_total->GetYaxis()->SetTitle("#sigma^{prod}_{#tilde{#nu_{#tau}}} #times BR ( #tilde{#nu_{#tau}} #rightarrow e#mu ) (fb)");
  graph_observed_noSyst_total->Draw("pl");  
  */

  TGraph *graph_expected_noSyst_total = new TGraph(counter_masses,masses,xs_expected_noSyst);
  graph_expected_noSyst_total->GetXaxis()->SetRangeUser(mass_min,mass_max);
  graph_expected_noSyst_total->GetYaxis()->SetRangeUser(0.1,1000.);
  graph_expected_noSyst_total->SetTitle("");
  graph_expected_noSyst_total->SetMarkerStyle(20);
  graph_expected_noSyst_total->SetMarkerColor(kGreen);
  graph_expected_noSyst_total->SetLineColor(kGreen);
  graph_expected_noSyst_total->SetLineWidth(2);
  graph_expected_noSyst_total->SetLineStyle(2);    
  graph_expected_noSyst_total->GetXaxis()->SetTitle("M_{#tilde{#nu_{#tau}}} (GeV)");
  graph_expected_noSyst_total->GetYaxis()->SetTitle("#sigma^{prod}_{#tilde{#nu_{#tau}}} #times BR ( #tilde{#nu_{#tau}} #rightarrow e#mu ) (fb)");
  graph_expected_noSyst_total->Draw("pl");  
  
  //  TGraph *graph_expected_noSyst_68_up_total = new TGraph(counter_masses,masses,xs_expected_noSyst_68_up);    
  // TGraph *graph_expected_noSyst_68_down_total = new TGraph(counter_masses,masses,xs_expected_noSyst_68_down);    
  TGraph *grshade_95_total_noSyst = new TGraph(2*counter_masses);
  for (int i=0;i<counter_masses;i++) {
    grshade_95_total_noSyst->SetPoint(i,masses[i],xs_expected_noSyst_95_up[i]);
    grshade_95_total_noSyst->SetPoint(counter_masses+i,masses[counter_masses-i-1],xs_expected_noSyst_95_down[counter_masses-i-1]);
  }
  
  grshade_95_total_noSyst->SetFillStyle(3004);
  grshade_95_total_noSyst->SetFillColorAlpha(kGreen, 0.35);
  // grshade_95_total_noSyst->SetFillColor(kGreen);
  // grshade_95_total_noSyst->Draw("f");
  
  //  TGraph *grshade_68_total = new TGraph(2*counter_masses);
  // for (int i=0;i<counter_masses;i++) {
  //  grshade_68_total->SetPoint(i,masses[i],xs_expected_noSyst_68_up[i]);
  // grshade_68_total->SetPoint(counter_masses+i,masses[counter_masses-i-1],xs_expected_noSyst_68_down[counter_masses-i-1]);
  // }
  
  //grshade_68_total->SetFillStyle(3005);
  //grshade_68_total->SetFillColor(kGreen+3);
  //grshade_68_total->Draw("f");

  graph_expected_noSyst_total->Draw("pl,same");  
  //graph_observed_noSyst_total->Draw("pl,same");

  //

  TLegend *leg_total = new TLegend(0.45,0.55,0.95,0.95);
  leg_total->SetFillColor(0);
  leg_total->SetTextFont(42);
  leg_total->SetTextSize(0.032);    
  
  //  leg_total->AddEntry(graph_observed_withSyst_total, "observed limit (with systematics)","pl");
  leg_total->AddEntry(graph_expected_withSyst_total, "expected limit (with top systematics)","pl"); 
  //leg_total->AddEntry(graph_observed_noSyst_total, "observed limit (no systematics)","pl");
  leg_total->AddEntry(graph_expected_noSyst_total, "expected limit (no top systematics)","pl"); 
  //leg_total->AddEntry(grshade_68_total, "68% expected","f");
  //leg_total->AddEntry(grshade_95_total, "95% band (with systematics)","f");
  //leg_total->AddEntry(grshade_95_total_noSyst, "95% band (no systematics)","f");
  //  leg_total->AddEntry(graph_xsec, "RPV signal (NLO)","");
  leg_total->AddEntry(graph_xsec, "RPV signal (#lambda^{I}_{311}=#lambda_{312}=0.1)","l");
  leg_total->Draw("same");
  
  TLatex* CMS_text = new TLatex(0.24,0.88,"CMS");
  CMS_text->SetNDC();
  CMS_text->SetTextSize(0.05);
  CMS_text->SetTextAngle(0);
  CMS_text->Draw("same");
  
  TLatex* CMS_text_2 = new TLatex(0.20,0.83,"Preliminary");
  CMS_text_2->SetNDC();
  CMS_text_2->SetTextFont(42);
  CMS_text_2->SetTextSize(0.05);
  CMS_text_2->SetTextAngle(0);
  CMS_text_2->Draw("same");    
  
  TLatex* lumiText = new TLatex(0.95,0.975,"2.5 fb^{-1} (13 TeV)");
  lumiText->SetNDC();
  lumiText->SetTextFont(42);
  lumiText->SetTextSize(0.04);
  lumiText->SetTextAlign(32);
  lumiText->Draw("same");     

  outfile->cd();
  std::cout<< "Prepare to write everything" << std::endl;
  
  //  graph_observed_withSyst_total->Write("limit_observed");
  graph_expected_withSyst_total->Write("limit_expected");    
  // graph_observed_noSyst_total->Write("limit_observed");
  graph_expected_noSyst_total->Write("limit_expected");    
  //total->Draw();
  total->Write("limit_plot");
  // graph_expected_withSyst_68_up_total->Write("limit_68_up");
  // graph_expected_withSyst_68_down_total->Write("limit_68_down");    
  //grshade_95_total->Write("limit_95_shade");
  //grshade_95_total_noSyst->Write("limit_95_shade");

}
