{
int N;
TFile f("../dat/run/signalMC/event_signalMC/jpsi2xi0_event.root", "read");
TCanvas *c1 = new TCanvas("c1", "M_{#Xi^{0}}", 800, 600);
gStyle->SetOptStat(0);
c1->SetFillColor(10);
c1->SetFrameFillColor(10);
TTree* tree = (TTree*) f.Get("pi0");
Double_t  xmin = 1.2; 
Double_t xmax = 1.5;
Int_t xbins = 200;
Double_t ytitle;
TH1F *h = new TH1F("h", "", xbins, xmin, xmax);
Double_t x[2000];
tree->SetBranchAddress("mxi0", &x);
N=tree->GetEntries();
tree->Draw("mxi0>>h");
h->SetLineColor(kRed);
h->Print();
h->SetXTitle("M_{#Xi^{0}} (GeV/c^{2})");
h->SetYTitle("Events/ (1.5 Mev/c^{2})");    //1.5 Mev
h->SetFillColor(10);
h->Draw("");
c1->Update();
c1->Print("Xi0.pdf");
}
