{
int N;
//SetStyle();
TFile f("../dat/run/signalMC/event_signalMC/jpsi2xi0_event.root", "read");
TCanvas *c1 = new TCanvas("c1", "M_{#gamma#gamma}", 800, 600);
gStyle->SetOptStat(0);
c1->SetFillColor(10);
c1->SetFrameFillColor(10);
TTree* tree = (TTree*) f.Get("pi0");
Double_t  xmin = 0.0; xmax = 0.3;
Int_t xbins = 300;
Double_t ytitle;
TH1F *h = new TH1F("h", "", xbins, xmin, xmax);
Double_t x[2000];
int run,ngamgam;
//tree->SetBranchAddress("ngamgam", &ngamgam);
tree->SetBranchAddress("mgamgam", x);
tree->SetBranchAddress("run", &run);
N=tree->GetEntries();
tree->Draw("mgamgam>>h");
h->SetLineColor(kRed);
//h->Print();
h->SetXTitle("M_{#gamma#gamma} (GeV/c^{2})");
h->SetYTitle("Events/ (1 Mev/c^{2})");//1 Mev
h->SetFillColor(10);
h->Draw("");
c1->Update();
c1->Print("gamgam.pdf");
}
