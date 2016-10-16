#include "RiceStyle.h"

using namespace std;

double pileup = 0.65; //fill the average pileup
double run_number = 281616; //fill the run number
bool doLogY = true;

void plotMBtriggerEff(){

	TFile* file[20];

	file[0] = new TFile("../rootfiles/MBtriggerEfficiency_v1.root");
	file[1] = new TFile("../rootfiles/MBtriggerEfficiency_v3_plus.root");
	file[2] = new TFile("../rootfiles/MBtriggerEfficiency_v3_minus.root");
	file[3] = new TFile("../rootfiles/MBtriggerEfficiency_v4.root");
	file[4] = new TFile("../rootfiles/MBtriggerEfficiency_v5.root");
	file[5] = new TFile("../rootfiles/MBtriggerEfficiency_v6.root");
	file[6] = new TFile("../rootfiles/MBtriggerEfficiency_v7.root");
	file[7] = new TFile("../rootfiles/MBtriggerEfficiency_v8.root");
	file[8] = new TFile("../rootfiles/MBtriggerEfficiency_v9.root");
	file[9] = new TFile("../rootfiles/MBtriggerEfficiency_v10.root");

	TH1D* base1 = makeHist("base1", "", "HF threshold (ADC)", "Efficiency", 40,0,40);
	
	TCanvas* c1 = makeCanvas("c1","c1", false, doLogY);

	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.15);
	gPad->SetTopMargin(0.1);
	gPad->SetTicks();

	if( !doLogY ) base1->GetYaxis()->SetRangeUser(0.00001,1.4); else base1->GetYaxis()->SetRangeUser(0.00001,130);

	base1->Draw();

	TH1F* eff1[20];
	TH1F* eff2[20];

	for(int bin = 0; bin < 10; bin++){

		eff1[bin] = (TH1F*) file[bin]->Get("accPerEvt");
		if(bin != 0) eff2[bin] = (TH1F*) file[bin]->Get("accPerEvtAnd");
	}

	for(int bin = 0; bin < 4; bin++){

		double norm1 = eff1[bin]->GetBinContent(1);
		if(bin != 0) double norm2 = eff2[bin]->GetBinContent(1);

		eff1[bin]->Scale(1.0/norm1);
		eff1[bin]->SetMarkerStyle(24);
		if(bin == 2) eff1[bin]->SetMarkerColor(8); else eff1[bin]->SetMarkerColor(bin+1);
		eff1[bin]->Draw("same");

		if(bin != 0){

			eff2[bin]->Scale(1.0/norm2);
			eff2[bin]->SetMarkerStyle(25);
			if(bin == 2) eff2[bin]->SetMarkerColor(8); else eff2[bin]->SetMarkerColor(bin+1);
			eff2[bin]->Draw("same");
		}
	
	}
	
	TLegend *w1 = new TLegend(0.5,0.70,0.8,0.87);
    w1->SetLineColor(kWhite);
    w1->SetFillColor(0);
    w1->SetTextSize(17);
    w1->SetTextFont(43);
    w1->AddEntry(eff1[0], "OR_ZeroBias", "P");
    w1->AddEntry(eff1[3], "OR_MinimumBias_PixelTrk", "P");
    w1->AddEntry(eff1[1], "OR_BPTXplusOnly", "P");
    w1->AddEntry(eff1[2], "OR_BPTXminusOnly", "P");
    w1->AddEntry(eff2[3], "AND_MinimumBias_PixelTrk", "P");
    w1->AddEntry(eff2[1], "AND_BPTXplusOnly", "P");
    w1->AddEntry(eff2[2], "AND_BPTXminusOnly", "P");
    w1->Draw("same");

   	TLatex* r11 = new TLatex(0.2,0.84, "CMS");
    r11->SetNDC();
    r11->SetTextSize(0.045);
    r11->Draw("same");

    TLatex* r22 = new TLatex(0.2,0.79, "Preliminary");
    r22->SetNDC();
    r22->SetTextSize(24);
    r22->SetTextFont(53);
    r22->Draw("same");


	TLatex* latex3 = new TLatex(0.47, 0.92, Form("Run=%.0f, pileup = %.2f", run_number, pileup) );
    latex3->SetNDC();
    latex3->SetTextSize(23);
    latex3->SetTextFont(43);
    latex3->SetTextColor(kBlack);
    latex3->Draw("same");


	TH1D* base2 = makeHist("base2", "", "HF threshold (ADC)", "Efficiency", 40,0,40);
	
	base2->GetYaxis()->SetRangeUser(0.00001,130);

	TCanvas* c2 = makeCanvas("c2","c2", false, true);
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.15);
	gPad->SetTopMargin(0.1);
	gPad->SetTicks();

	base2->Draw();

	double norm1 = eff1[4]->GetBinContent(1);
	double norm2 = eff2[4]->GetBinContent(1);

	eff1[4]->Scale(1.0/norm1);
	eff1[4]->SetMarkerStyle(24);
	eff1[4]->SetMarkerColor(kBlack);
	eff1[4]->Draw("same");

	eff2[4]->Scale(1.0/norm2);
	eff2[4]->SetMarkerStyle(25);
	eff2[4]->SetMarkerColor(kBlack);
	eff2[4]->Draw("same");

	eff1[5]->Scale(1.0/norm1);
	eff1[5]->SetMarkerStyle(24);
	eff1[5]->SetMarkerColor(kRed);
	eff1[5]->Draw("same");

	eff2[5]->Scale(1.0/norm2);
	eff2[5]->SetMarkerStyle(25);
	eff2[5]->SetMarkerColor(kRed);
	eff2[5]->Draw("same");
	
	eff1[6]->Scale(1.0/norm1);
	eff1[6]->SetMarkerStyle(24);
	eff1[6]->SetMarkerColor(8);
	eff1[6]->Draw("same");

	eff2[6]->Scale(1.0/norm2);
	eff2[6]->SetMarkerStyle(25);
	eff2[6]->SetMarkerColor(8);
	eff2[6]->Draw("same");

	TLegend *w2 = new TLegend(0.5,0.70,0.8,0.87);
    w2->SetLineColor(kWhite);
    w2->SetFillColor(0);
    w2->SetTextSize(17);
    w2->SetTextFont(43);
    w2->AddEntry(eff1[4], "OR_ZeroBias", "P");
    w2->AddEntry(eff1[5], "OR_BPTXplusOnly", "P");
    w2->AddEntry(eff1[6], "OR_BPTXminusOnly", "P");
    w2->AddEntry(eff2[4], "AND_ZeroBias", "P");
    w2->AddEntry(eff2[5], "AND_BPTXplusOnly", "P");
    w2->AddEntry(eff2[6], "AND_BPTXminusOnly", "P");
    w2->Draw("same");

    run_number = 247324;
    pileup = 0.013;

	TLatex* latex4 = new TLatex(0.47, 0.92, Form("Run=%.0f, pileup = %.2f", run_number, pileup) );
    latex4->SetNDC();
    latex4->SetTextSize(23);
    latex4->SetTextFont(43);
    latex4->SetTextColor(kBlack);
    latex4->Draw("same");

    r11->Draw("same");
    r22->Draw("same");


	TH1D* base3 = makeHist("base3", "", "HF threshold (ADC)", "Efficiency", 40,0,40);
	
	base3->GetYaxis()->SetRangeUser(0.0000001,130);

	TCanvas* c3 = makeCanvas("c3","c3", false, true);
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.15);
	gPad->SetTopMargin(0.1);
	gPad->SetTicks();

	base3->Draw();

	double norm1 = eff1[7]->GetBinContent(1);
	double norm2 = eff2[7]->GetBinContent(1);

	eff1[7]->Scale(1.0/norm1);
	eff1[7]->SetMarkerStyle(24);
	eff1[7]->SetMarkerColor(kBlack);
	eff1[7]->Draw("same");

	eff2[7]->Scale(1.0/norm2);
	eff2[7]->SetMarkerStyle(25);
	eff2[7]->SetMarkerColor(kBlack);
	eff2[7]->Draw("same");

	eff1[8]->Scale(1.0/norm1);
	eff1[8]->SetMarkerStyle(24);
	eff1[8]->SetMarkerColor(kRed);
	eff1[8]->Draw("same");

	eff2[8]->Scale(1.0/norm2);
	eff2[8]->SetMarkerStyle(25);
	eff2[8]->SetMarkerColor(kRed);
	eff2[8]->Draw("same");
	
	eff1[9]->Scale(1.0/norm1);
	eff1[9]->SetMarkerStyle(24);
	eff1[9]->SetMarkerColor(8);
	eff1[9]->Draw("same");

	eff2[9]->Scale(1.0/norm2);
	eff2[9]->SetMarkerStyle(25);
	eff2[9]->SetMarkerColor(8);
	eff2[9]->Draw("same");

	TLegend *w3 = new TLegend(0.5,0.70,0.8,0.87);
    w3->SetLineColor(kWhite);
    w3->SetFillColor(0);
    w3->SetTextSize(17);
    w3->SetTextFont(43);
    w3->AddEntry(eff1[7], "OR_HIZeroBias", "P");
    w3->AddEntry(eff1[8], "OR_HIBPTXplusOnly", "P");
    w3->AddEntry(eff1[9], "OR_HIBPTXminusOnly", "P");
    w3->AddEntry(eff2[7], "AND_HIZeroBias", "P");
    w3->AddEntry(eff2[8], "AND_HIBPTXplusOnly", "P");
    w3->AddEntry(eff2[9], "AND_HIBPTXminusOnly", "P");
    w3->Draw("same");

    run_number = 262640;
    pileup = 0.0015;

	TLatex* latex5 = new TLatex(0.47, 0.92, Form("Run=%.0f, pileup = %.4f", run_number, pileup) );
    latex5->SetNDC();
    latex5->SetTextSize(23);
    latex5->SetTextFont(43);
    latex5->SetTextColor(kBlack);
    latex5->Draw("same");

    r11->Draw("same");
    r22->Draw("same");


	



}