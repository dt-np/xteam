{
int N;
TFile f("../dat/run/signalMC/event_signalMC/jpsi2xi0_event.root", "read");
TCanvas *c1 = new TCanvas("c1", "recoil of M_{#Xi^{0}}", 800, 600);
gStyle->SetOptStat(0);
c1->SetFillColor(10);
c1->SetFrameFillColor(10);
TTree* tree = (TTree*) f.Get("pi0");
Double_t  xmin = 0.8; 
Double_t xmax = 1.8;
Int_t xbins = 200;
Double_t ytitle;
TH1F *h = new TH1F("h", "", xbins, xmin, xmax);
Double_t x[2000];
tree->SetBranchAddress("mrecxi0", &x);
N=tree->GetEntries();
tree->Draw("mrecxi0>>h");
h->SetLineColor(kRed);
h->Print();
h->SetXTitle("recoil of M_{#Xi^{0}} (GeV/c^{2})");
h->SetYTitle("Events/ (5 Mev/c^{2})");//0.7 Mev
h->SetFillColor(10);
h->Draw("");
c1->Update();
c1->Print("rec_Xi0.pdf");
}
