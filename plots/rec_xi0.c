{
int N;
TFile f("../dat/run/signalMC/event_signalMC/jpsi2xi0_event.root", "read");
TCanvas *c1 = new TCanvas("c1", "recoil of M_{#Xi^{0}}", 800, 600);
gStyle->SetOptStat(0);
c1->SetFillColor(10);
c1->SetFrameFillColor(10);
TTree* tree = (TTree*) f.Get("pi0");
Double_t  xmin = 1.1; 
Double_t xmax = 1.5;
Int_t xbins = 200;
Double_t ytitle;
TH1F *h = new TH1F("h", "", xbins, xmin, xmax);
// Double_t x[2000];
// tree->SetBranchAddress("mrecxi0", &x);
N=tree->GetEntries();
// tree->Draw("mrecxi0>>h"," mxi0>1.25 && mxi0<1.40 "," mlambda>1.11 && mlambda<1.12 ");
tree->Draw("mrecxi0>>h"," (mxi0>1.30486 && mxi0<1.32486) && (mlambda>1.110683 && mlambda<1.120683)");
h->SetLineColor(kRed);
h->Print();
h->SetXTitle("recoil of M_{#Xi^{0}} (GeV/c^{2})");
h->SetYTitle("Events/ (2 Mev/c^{2})");  //3.0 Mev
h->SetFillColor(10);
h->Draw("");
c1->Update();
c1->Print("rec_Xi0.pdf");
}
