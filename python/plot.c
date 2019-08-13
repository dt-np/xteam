{
        int N;
TFile f("../run/root_jpsiantisigmaminussigmaplus/jpsiantisigmaminussigmaplus_gen_mc.root", "read");
gStyle->SetOptStat(0);
TTree* tree = (TTree*) f.Get("tree");
TH1F *h = new TH1F("", "", 1000, -20 ,20);
double x,y,z;
tree->SetBranchAddress("vr0", &x);
N=tree->GetEntries();
for (int i=0;i<N;i++){
        tree->GetEntry(i);
        h->Fill(x);
}
h->SetLineColor(kRed);
h->Print();
h->GetXaxis()->SetTitle("vr0");
h->GetYaxis()->SetTitle("entries");
h->Draw();
h->SaveAs("plot2.pdf");

}

