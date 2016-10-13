#include "RiceStyle.h"

using namespace std;

void plotMBtriggerEff(){

	TFile* file1 = new TFile("../rootfiles/MBtriggerEfficiency_v1.root");
	TFile* file2 = new TFile("../rootfiles/MBtriggerEfficiency_v2_plus.root");
	TFile* file3 = new TFile("../rootfiles/MBtriggerEfficiency_v2_minus.root");

	TH1D* base = makeHist("base", "", "HF threshold (ADC)", "Efficiency", 40,0,40);
	TCanvas* c1 = makeCanvas("c1","c1", false, false);
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.15);
	gPad->SetTopMargin(0.1);
	gPad->SetTicks();

	TH1F* eff1 = (TH1F*) file1->Get("accPerEvt");
	TH1F* eff2 = (TH1F*) file2->Get("accPerEvt");
	TH1F* eff3 = (TH1F*) file3->Get("accPerEvt");

	base->GetYaxis()->SetRangeUser(0,1.3);
	base->Draw();

	eff1->Scale(1.0/20);
	eff1->SetMarkerStyle(24);
	eff1->SetMarkerColor(kBlack);
	eff1->Draw("same");

	eff2->Scale(1.0/37);
	eff2->SetMarkerStyle(24);
	eff2->SetMarkerColor(kBlue);
	eff2->Draw("same");

	eff3->Scale(1.0/37);
	eff3->SetMarkerStyle(24);
	eff3->SetMarkerColor(kRed);
	eff3->Draw("same");

	TH1D* diff = new TH1D("diff","diff",40,0,40);

	for(int bin = 0; bin < eff1->GetNbinsX(); bin++){

		double total = eff1->GetBinContent(bin+1);
		double noise = eff2->GetBinContent(bin+1) + eff3->GetBinContent(bin+1);

		double efficiency = (total-noise)/((1.0-noise)*(1-TMath::Exp(-0.65)));

		diff->SetBinContent(bin+1, efficiency);


	}

	diff->SetMarkerStyle(20);
	diff->SetMarkerColor(kGreen-2);
	diff->Draw("Psame");

	TLegend *w1 = new TLegend(0.6,0.6,0.75,0.8);
    w1->SetLineColor(kWhite);
    w1->SetFillColor(0);
    w1->SetTextSize(23);
    w1->SetTextFont(43);
    w1->AddEntry(eff1, "Total", "P");
    w1->AddEntry(eff2, "BPTXplusOnly", "P");
    w1->AddEntry(eff3, "BPTXminusOnly", "P");
    w1->AddEntry(diff, "SignalOnly", "P");
    w1->Draw("same");


	TLatex* latex3 = new TLatex(0.2, 0.83, "Run=281616, lumi[270,464]");
    latex3->SetNDC();
    latex3->SetTextSize(23);
    latex3->SetTextFont(43);
    latex3->SetTextColor(kBlack);
    latex3->Draw("same");

    TLine* l1 = new TLine(0,0.65,20,0.65);
    l1->SetLineColor(kBlue);
    l1->SetLineStyle(2);
    l1->SetLineWidth(2);
    //l1->Draw("same");

	
	TLatex* latex3 = new TLatex(0.2, 0.78, "#LTpileup#GT = 0.65");
    latex3->SetNDC();
    latex3->SetTextSize(23);
    latex3->SetTextFont(43);
    latex3->SetTextColor(kBlack);
    latex3->Draw("same");


}