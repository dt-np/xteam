
{
int N;
//SetStyle();
TFile f("../dat/run/signalMC/event_signalMC/jpsi2xi0_event.root", "read");
TCanvas *c1 = new TCanvas("c1", "M_{#gamma#gamma}", 800, 600);
//gStyle->SetOptStat(0);
TTree* tree = (TTree*) f.Get("pi0");
Double_t  xmin = 0.0;
Double_t xmax = 0.3;
Int_t xbins = 300;
Double_t ytitle;
TH1F *h = new TH1F("h", "M_{#pi^{0}}", xbins, xmin, xmax);
Double_t x[2000];
int run,ngamgam;
//tree->SetBranchAddress("ngamgam", &ngamgam);
tree->SetBranchAddress("mgamgam", x);
tree->SetBranchAddress("run", &run);
N=tree->GetEntries();
//for (int i=0;i<20;i++){
//	tree->GetEntry(i);
//	cout<<i<<endl;
//	if (ngamgam>0){
//		cout<<run<<" "<<" "<<x[0]<<endl;
//	}
//}
tree->Draw("mgamgam>>h");
h->SetLineColor(kRed);
//h->Print();
h->SetXTitle("invariant mass of M_{#gamma#gamma} (GeV/c^{2})");
h->SetYTitle("Events/ (1 Mev/c^{2})");//1 Mev
//h->Rebin(2);
//c1->cd();
h->Draw("");
c1->Update();
c1->Print("gamgam.pdf");
}
