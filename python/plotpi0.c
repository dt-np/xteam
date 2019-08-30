{
        int N;
TFile f("../run/root_jpsiantisigmaminussigmaplus/jpsiantisigmaminussigmaplus_gen_mc.root", "read");
//gStyle->SetOptStat(0);
TTree* tree = (TTree*) f.Get("tree");
TH1F *h = new TH1F("", "", 100, -0.1,0.5);
double x,y,z;
tree->SetBranchAddress("m_kmfit_mass", &x);
N=tree->GetEntries();
for (int i=0;i<N;i++){
        tree->GetEntry(i);
        h->Fill(x);
}
        h->SetLineColor(kRed);
        h->Print();
        h->GetXaxis()->SetTitle("m_kmfit_masss");
        h->GetYaxis()->SetTitle("entries");
        h->Draw();
}
