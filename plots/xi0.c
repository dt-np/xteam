{
int N;
TFile f("../dat/run/signalMC/event_signalMC/jpsi2xi0_event.root", "read");
TCanvas *c1 = new TCanvas("c1", "M_{#Xi^{0}}", 800, 600);
gStyle->SetOptStat(0);
c1->SetFillColor(10);
c1->SetFrameFillColor(10);
TTree* tree = (TTree*) f.Get("pi0");
Double_t  xmin = 1.25; 
Double_t xmax = 1.40;
Int_t xbins = 150;
Double_t ytitle;
TH1F *h = new TH1F("h", "", xbins, xmin, xmax);
//Double_t x[2000];
//tree->SetBranchAddress("mxi0", &x);
N=tree->GetEntries();
tree->Draw("mxi0>>h"," mlambda>1.110683 && mlambda<1.120683 ");
h->SetLineColor(kRed);
h->Print();
h->SetXTitle("M_{#Xi^{0}} (GeV/c^{2})");
h->SetYTitle("Events/ (1.0 Mev/c^{2})");  //1.0 Mev
h->SetFillColor(10);
h->Draw("");
TArrow arrow1,arrow2;
arrow1.SetLineColor(2);
arrow1.SetLineWidth(3);
arrow1.DrawArrow(1.304,50,1.304,0,0.02,"->");    //the begin point and end point's location,line side,line style...
arrow2.SetLineColor(2);
arrow2.SetLineWidth(3);
arrow2.DrawArrow(1.324,50,1.324,0,0.02,"->");    //the begin point and end point's location,line side,line style...
c1->Update();
c1->Print("Xi0.pdf");
}
