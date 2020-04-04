//#include "/afs/ihep.ac.cn/users/g/gushan/rootscript/bes3plotstyle.C"
//#include <math.h>
//using namespace std;
//void plotpi0()
{
int N;
//SetStyle();
//TFile f("../dat/run/signalMC/event_signalMC/jpsi2xi0_event.root", "read");
//TFile f("../dat/run/jpsi_inclusive/merge_root_event09/jpsi_data09_event_merged_1.root", "read");
TFile f("../dat/run/jpsi_inclusive/merge_root_event09/jpsi_inclusiveMC_event_merged_1.root", "read");
//TFile f("~/bes/hypermiss/dat/run/jpsi_inclusive/rootfile_data09/jpsi_data09-327.root");
TCanvas *c1 = new TCanvas("c1", "M_{#gamma#gamma}", 800, 600);
//gStyle->SetOptStat(0);
TTree* tree = (TTree*) f.Get("tree");
Double_t  xmin = 0.0;
Double_t xmax = 0.5;
Int_t xbins = 200;
Double_t ytitle;
TH1F *h = new TH1F("h", "M_{#gamma#gamma}", xbins, xmin, xmax);
Double_t x[2000];
int run,ngamgam;
tree->SetBranchAddress("ngamgam", &ngamgam);
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
h->Print();
h->SetXTitle("M_{#gamma#gamma} (GeV/c^{2})");
h->SetYTitle("Events/ (2.5 Mev/c^{2})");//2.5 Mev
c1->cd();
h->Draw();
c1->Update();
c1->Print("gamgam_incl.pdf");
}
