#include "RiceStyle.h"

using namespace std;

double pileup = 0.65; //fill the average pileup
double run_number = 281616; //fill the run number

void plotMBtriggerEff_Ntrk(){

  	TH1F::SetDefaultSumw2();


	TFile* file[10];

	file[0] = new TFile("../rootfiles/MBtriggerEfficiency_v19.root");

	TH1F* eff1[10];
	TH1F* eff2[10];

	eff1[0] = (TH1F*) file[0]->Get("accPerEvtThrFile");
	eff2[0] = (TH1F*) file[0]->Get("accPerEvtThrFileDeno");

	TH1D* eff_1_temp = new TH1D("eff_1", "eff_1", 1000, 0,1000);
	TH1D* eff_2_temp = new TH1D("eff_2", "eff_2", 1000, 0,1000);

	for(int bin = 0; bin < eff1[0]->GetNbinsX(); bin ++ ){
		
		double value = eff1[0]->GetBinContent(bin+1);
		double err = eff1[0]->GetBinError(bin+1);
		
		eff_1_temp->SetBinContent(bin+1, value);
		eff_1_temp->SetBinError( bin+1, err/37.0 );

		double value = eff2[0]->GetBinContent(bin+1);
		double err = eff2[0]->GetBinError(bin+1);
		
		eff_2_temp->SetBinContent(bin+1, value);
		eff_2_temp->SetBinError( bin+1, err/37.0 );

	}

	TH1D* base1 = makeHist("base1", "", "N^{offline}_{trk}", "Efficiency (HF_OR 17ADC)", 200,0,200);
	base1->GetXaxis()->SetRangeUser(0,100);
	base1->GetYaxis()->SetRangeUser(0.4,1.15);

	TCanvas* c1 = makeCanvas("c1","c1", false, false);
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.15);
	gPad->SetTopMargin(0.1);
	gPad->SetTicks();

	base1->Draw();
	
	TGraphAsymmErrors* gr[10];
	gr[0] = new TGraphAsymmErrors();
	gr[0]->BayesDivide( eff_1_temp, eff_2_temp, "cp" );
	gr[0]->SetMarkerStyle(24);
	gr[0]->SetMarkerColor(kBlack);
	gr[0]->Draw("Psame");

	TLatex* latex4 = new TLatex(0.47, 0.92, Form("Run=%.0f, pileup = %.2f", run_number, pileup) );
    latex4->SetNDC();
    latex4->SetTextSize(23);
    latex4->SetTextFont(43);
    latex4->SetTextColor(kBlack);
    latex4->Draw("same");

	TLatex* latex1 = new TLatex(0.2, 0.2, "ZeroBias_PixelTrack" );
    latex1->SetNDC();
    latex1->SetTextSize(23);
    latex1->SetTextFont(43);
    latex1->SetTextColor(kBlack);
    latex1->Draw("same");

   	TLatex* r11 = new TLatex(0.2,0.84, "CMS");
    r11->SetNDC();
    r11->SetTextSize(0.045);
    r11->Draw("same");

    TLatex* r22 = new TLatex(0.2,0.79, "Preliminary");
    r22->SetNDC();
    r22->SetTextSize(24);
    r22->SetTextFont(53);
    r22->Draw("same");



}





