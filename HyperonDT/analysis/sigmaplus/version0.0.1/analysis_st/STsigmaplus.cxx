#include "/afs/ihep.ac.cn/users/amitraahul/.rootInclude.h"
#include "/afs/ihep.ac.cn/users/amitraahul/bes/hypermiss/HyperonDT/analysis/MySelections/MySelections.h"

void STsigmaplus(string filelist = "", char* nfname="", bool isIncl = false){
	gStyle->SetOptStat(0);
	MySelections *mySelections = new MySelections("mySelections","");


	TFile* newf = new TFile(nfname,"recreate");
	TTree* ntree= new TTree("st","");


	TChain chain("Sigmaplus","");

	string filename;
	ifstream is(filelist.c_str());
	while(getline(is,filename))
	{
		chain.Add(filename.c_str());
		cout<<" filename "<<filename<<endl;
		
	}
	cout<<"entries "<<chain.GetEntries()<<endl; 


	Int_t run,event;
	Int_t indexmc;
	Double_t p4truth[100][6];

	Int_t g1Id, g2Id, pId;// reconstruct (pbar pi0)
	Int_t nshw, ngshw, ngcharged, ngproton, ncharged;
	Double_t p4shw[20][7], p4proton[10][9];


	chain.SetBranchAddress("run", &run);
	chain.SetBranchAddress("event", &event);
	if(isIncl){
		chain.SetBranchAddress("indexmc", &indexmc);
		chain.SetBranchAddress("p4truth", &p4truth);
	}
	chain.SetBranchAddress("g1Id", &g1Id);
	chain.SetBranchAddress("g2Id", &g2Id);
	chain.SetBranchAddress("pId", &pId);
	chain.SetBranchAddress("ngshw", &ngshw);
	chain.SetBranchAddress("nshw", &nshw);
	chain.SetBranchAddress("ncharged", &ncharged);
	chain.SetBranchAddress("ngcharged", &ngcharged);
	chain.SetBranchAddress("ngproton", &ngproton);
	chain.SetBranchAddress("p4shw", &p4shw);
	chain.SetBranchAddress("p4proton", &p4proton);


for(int n=0; n<chain.GetEntries(); n++)
	{
		chain.GetEntry(n);

		if(ngproton == 0) continue;

		//================================
		//  anti-Sigma- => pbar pi0
		//================================

		int protonId = pId;
		TLorentzVector p4p;
		int chargeP;
		double Vx,Vy,Vz;
		for(int a=0; a<ngproton; a++){
			int id_this = p4proton[a][5];
			if(id_this != protonId) continue;
			chargeP = p4proton[a][4];
			for(int b=0; b<4; b++) p4p[b] = p4proton[a][b];
			Vx = p4proton[a][6];
			Vy = p4proton[a][7];
			Vz = p4proton[a][8];
		}
		n_pcharge = chargeP;


		TLorentzVector p4g1, p4g2;
		TLorentzVector p4g1t, p4g2t;//E(gam) = E(TOF) + E(EMC)
		for(int a=0; a<nshw; a++){
			int id_this = p4shw[a][4];
			double etof = p4shw[a][6];
			if(etof  < 0){
			//cout<<"etof = "<<etof<<" means TofTrack not valid, etof set to be 0"<<endl;
			etof = 0;
			}
if(id_this == g1Id)	{
				for(int b=0; b<3; b++) {
					p4g1[b] = p4shw[a][b];
					p4g1t[b]= p4shw[a][b];
				}
				p4g1[3] = p4shw[a][3];
				p4g1t[3] = p4shw[a][3] + etof;
			}
			if(id_this == g2Id)	{
				for(int b=0; b<3; b++){
				   	p4g2[b] = p4shw[a][b];
				   	p4g2t[b]= p4shw[a][b];
				}
				p4g2[3] = p4shw[a][3];
				p4g2t[3] = p4shw[a][3] + etof;
			}
		}

		TLorentzVector p4gg = p4g1 + p4g2;
		TLorentzVector p4st = p4p + p4g1 +p4g2;
		TLorentzVector p4_rmst = mySelections->GetP4cms() - p4st;
		TLorentzVector p4_rmgg = mySelections->GetP4cms() - p4gg;

		TLorentzVector p4ggt= p4g1t + p4g2t;
		TLorentzVector p4stt = p4p + p4g1t +p4g2t;
		TLorentzVector p4_rmstt = mySelections->GetP4cms() - p4stt;
		TLorentzVector p4_rmggt = mySelections->GetP4cms() - p4ggt;

		//-----------for continuum------------
		//TLorentzVector p4cms_con(3.08*0.011, 0,0, 3.08);
		//TLorentzVector p4_rmst = p4cms_con - p4st;
		//TLorentzVector p4_rmgg = p4cms_con - p4gg;
		
		n_run = run;
		n_event = event;
		n_mgg = p4gg.M();
		n_rmgg = p4_rmgg.M();
		n_Mpgg= p4st.M();
		n_RMpgg= p4_rmst.M();
		n_mpgg= p4st.M() - p4gg.M() + mySelections->GetMassPi0();
		n_rmpgg= p4_rmst.M() + p4gg.M() - mySelections->GetMassPi0()
		//E(gam) = E(TOF)+E(EMC)
		n_mggt = p4ggt.M();
		n_rmggt = p4_rmggt.M();
		n_Mpggt= p4stt.M();
		n_RMpggt= p4_rmstt.M();
		n_mpggt= p4stt.M() - p4ggt.M() + mySelections->GetMassPi0();
		n_rmpggt= p4_rmstt.M() + p4ggt.M() - mySelections->GetMassPi0();

		n_vx = Vx;
		n_vy = Vy;
		n_vz = Vz;
		n_vr = sqrt(Vx*Vx + Vy*Vy);

		//boost into p pi0 frame
		TLorentzVector p4_parent(p4st);
		TLorentzVector p4p_boost(p4p);
		TVector3 boostVector = p4_parent.BoostVector();
		p4p_boost.Boost(-boostVector);
		n_pbst = p4p_boost.P();


		if(isIncl){
			for(int b=0; b<indexmc; b++)
			{
				n_motheridx[b] = p4truth[b][5];
				n_pdgid[b] = p4truth[b][4];
			}
			n_indexmc = indexmc;
		}
		ntree->Fill();

	}
	newf->cd();
	ntree->Write();
	newf->Close();

	cout<<"finish"<<endl;
}
