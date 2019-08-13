{
        int N;
TFile f("../run/root_jpsiantisigmaminussigmaplus/jpsiantisigmaminussigmaplus_gen_mc.root", "read");
gStyle->SetOptStat(0);
TTree* tree = (TTree*) f.Get("tree");
TH1F *h = new TH1F("", "", 1000, -20 ,20);
//TH1F *h1 = new TH1F("", "", 1000, 0 ,3);
//TH1F *h2 = new TH1F("", "", 1000, 0 ,3);
double x,y,z;
tree->SetBranchAddress("vr0", &x);
//tree->SetBranchAddress("br_y", &y);
//tree->SetBranchAddress("br_z", &z);
N=tree->GetEntries();
for (int i=0;i<N;i++){
        tree->GetEntry(i);
        h->Fill(x);
       // h1->Fill(z);
       // h2->Fill(x);
}
h->SetLineColor(kRed);
//h2->SetLineColor(kYellow);
h->Print();
h->GetXaxis()->SetTitle("vr0");
h->GetYaxis()->SetTitle("entries");
h->Draw();
h->SaveAs("plot2.pdf");
//h1->Draw("same");
//h2->Draw("same");

}

