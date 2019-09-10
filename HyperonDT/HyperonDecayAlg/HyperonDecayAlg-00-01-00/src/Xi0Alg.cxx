#include "HyperonDecayAlg/Xi0Alg.h"
#include "HyperonDecayAlg/LambdaFinder.h"
#include "HyperonDecayAlg/defs.h"


Xi0Alg::Xi0Alg(const std::string& name, ISvcLocator* pSvcLocator):Algorithm(name,pSvcLocator){
		declareProperty("SaveMCTruth",   m_saveMcTruth=true);

}
Xi0Alg::~Xi0Alg(){
	//add your code for deconstructor
}






// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

StatusCode Xi0Alg::initialize(){
	MsgStream log(msgSvc(), name());
	log<<MSG::INFO<<"Xi0Alg::initialize()"<<endreq;
	//add your code here
	StatusCode status;
	NTuplePtr nt1(ntupleSvc(), "FILE1/xi0");
	if ( nt1 ) m_tuple1 = nt1;
	else {
		m_tuple1 = ntupleSvc()->book ("FILE1/xi0", CLID_ColumnWiseTuple, "xi0 N-Tuple example");
		if ( m_tuple1 )    {
			status = m_tuple1->addItem ("run",   m_run);
			status = m_tuple1->addItem ("event", m_event);
			if(m_saveMcTruth){
				status = m_tuple1->addItem("indexmc",          m_idxmc, 0, 100);
				status = m_tuple1->addIndexedItem("p4truth",   m_idxmc, 6, m_p4truth);
			}

			status = m_tuple1->addItem ("nshw",   m_nshower, 0, 15);
			status = m_tuple1->addItem ("ngshw",   m_ngshower, 0, 15);
			status = m_tuple1->addIndexedItem ("p4shw", m_ngshower, 6, m_p4shw);

			status = m_tuple1->addItem ("ncharged",   m_ncharged, 0, 15);
			status = m_tuple1->addItem ("ngcharged",   m_ngcharged, 0, 15);
			status = m_tuple1->addItem ("ne", m_ne, 0, 15);
			status = m_tuple1->addIndexedItem ("p4e", m_ne, 6, m_p4e);

			status = m_tuple1->addItem ("nlvar", m_nlvar,0,12);
			status = m_tuple1->addIndexedItem ("p4lambda", m_nlvar, m_p4lambda);
			status = m_tuple1->addItem ("Idshw1", m_Idshw1);
			status = m_tuple1->addItem ("Idshw2", m_Idshw2);
			status = m_tuple1->addIndexedItem ("p4pi", m_nlvar, m_p4pi);
			status = m_tuple1->addItem ("notherLambda", m_notherLambda, 0,10);
			status = m_tuple1->addIndexedItem ("p4otherLambda", m_notherLambda, 6, m_p4otherLambda);

		}
		else    {
			log << MSG::ERROR << "    Cannot book N-tuple:" << long(m_tuple1) << endmsg;
			return StatusCode::FAILURE;
		}
	}
	for(int a=0; a<6; a++) Num[a] = 0;
	return StatusCode::SUCCESS;

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

StatusCode Xi0Alg::beginRun(){
	MsgStream log(msgSvc(), name());
	log<<MSG::INFO<<"Xi0Alg::beginRun()"<<endreq;
	//add your code here
	return StatusCode::SUCCESS;

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

StatusCode Xi0Alg::execute(){

	MsgStream log(msgSvc(), name());
	log<<MSG::INFO<<"Xi0Alg::execute()"<<endreq;

	SmartDataPtr<Event::EventHeader> eventHeader(eventSvc(),"/Event/EventHeader");
	if(!eventHeader){
		log<<MSG::INFO<<" EventHeader not found "<<endreq;
		return StatusCode::SUCCESS;
	}
	m_run = eventHeader->runNumber();
	m_event = eventHeader->eventNumber();
	if(m_run%10000==0)log << MSG::WARNING <<"run, evtnum = " << m_run << " , " << m_event <<endreq;

	if ( m_saveMcTruth &&  eventHeader->runNumber()<0)  mc_truth();

	// Begin to select events
	// to retrieve RecEvent
	SmartDataPtr<EvtRecEvent> evtRecEvent(eventSvc(), "/Event/EvtRec/EvtRecEvent");
	if ( ! evtRecEvent ) { 
		log << MSG::FATAL << "Could not find EvtRecEvent" << endl;
		return StatusCode::SUCCESS;
	}   
	// to retrieve RecTrackCol
	SmartDataPtr<EvtRecTrackCol> evtRecTrkCol( eventSvc(), "/Event/EvtRec/EvtRecTrackCol");
	if ( ! evtRecTrkCol ) { 
		log << MSG::FATAL << "Could not find EvtRecTrackCol" << endl;
		return StatusCode::SUCCESS;
	}



	Num[0] += 1;


	//==============================================
	//  Xi0 -> Lambda pi0
	//		   Lambda -> p pi-
	//==============================================

	MyTools* myTools;

	int totalCharged = evtRecEvent->totalCharged();
	if (totalCharged ==0 || totalCharged >12) return StatusCode::SUCCESS;
	Num[1] += 1;

	//-------------------------------------------------------------------
	//                 find Lambda candidate
	//  basic cuts, chiq; chiq_sec; L/sigma_L; mass signal window
	//-------------------------------------------------------------------
	vector<int> Vid1, Vid2;
	Vid1.clear(); Vid2.clear();
	vector<HepLorentzVector> Vp4L;
	Vp4L.clear();
	vector<int> Vflavor;
	Vflavor.clear();
	for(int c =0 ; c<totalCharged; c++){
		EvtRecTrackIterator itTrk1 = evtRecTrkCol->begin() + c;
		for(int d = c+1; d <totalCharged; d++){
			EvtRecTrackIterator itTrk2 = evtRecTrkCol->begin() + d;

			LambdaFinder lFinder;
			int findFlag = lFinder.LambdaSelector(c, d, evtRecTrkCol);
			if(findFlag != 1) continue;
			HepLorentzVector p4candidate = lFinder.getP4sec();
			double mass_this = p4candidate.m();
			double dl_this =  lFinder.getdlsec()/lFinder.getdlesec();
			double chiq_sec = lFinder.getchiqsec();

			double massdiff = mass_this - myTools->getMassLambda();
			//
			if(dl_this <= 2.0 ) continue;
			if(chiq_sec >= 200.) continue;
			if(fabs(massdiff) >= 0.03) continue;

			Vid1.push_back( c );
			Vid2.push_back( d );
			Vp4L.push_back(p4candidate);
			Vflavor.push_back( lFinder.getFlavorFlag() );
		}
	}

	if(Vid1.size() == 0) return StatusCode::SUCCESS;
	Num[2] += 1;




	//pi0 candidate 
	int nphoton = evtRecEvent->totalNeutral();
	if(nphoton>10) return StatusCode::SUCCESS;
	std::vector<int> iGoodGam;   iGoodGam.clear();
	myTools->selectNeutralTracks(evtRecEvent, evtRecTrkCol, iGoodGam);
	if ( iGoodGam.size() < 2  || iGoodGam.size() > 10 ) return StatusCode::SUCCESS;
	m_ngshower = iGoodGam.size();
	m_nshower  = nphoton;
	Num[3] += 1;


	vector<int> VIdG1, VIdG2;
	VIdG1.clear();
	VIdG2.clear();
	for(int i=0;i<iGoodGam.size();i++)
	{
		EvtRecTrackIterator itTrk1 = evtRecTrkCol->begin() + iGoodGam[i];
		HepLorentzVector p4G1 = myTools->getGammaP4(itTrk1);
		for(int j=i+1;j<iGoodGam.size();j++)
		{
			EvtRecTrackIterator itTrk2 = evtRecTrkCol->begin() + iGoodGam[j];
			HepLorentzVector p4G2 = myTools->getGammaP4(itTrk2);

			HepLorentzVector p4GG = p4G1 + p4G2;
			double mgg_this = p4GG.m();

			if(mgg_this < 0.11 || mgg_this > 0.15) continue;
			VIdG1.push_back( (*itTrk1)->trackId()  );
			VIdG2.push_back( (*itTrk2)->trackId()  );  
		}   
	}   
	if(VIdG1.size() == 0) return StatusCode::SUCCESS;


	//---------------------------------
	// combine Lambda with another pi0
	//---------------------------------
	double deltaMass = 99.;
	int id1_best, id2_best, idL_best, idpi0_best;
	for(int i=0; i<Vid1.size(); i++)
	{
		int id1_this = Vid1[i];
		int id2_this = Vid2[i];

		HepLorentzVector p4candidate = Vp4L[i];;
		int flavorFlag = Vflavor[i];//1 Lambda, -1 anti-Lambda

		for(int ii=0; ii<VIdG1.size(); ii++){
			EvtRecTrackIterator itTrk1 = evtRecTrkCol->begin() + VIdG1[ii];
			EvtRecTrackIterator itTrk2 = evtRecTrkCol->begin() + VIdG2[ii];
			HepLorentzVector p4G1 = myTools->getGammaP4(itTrk1);
			HepLorentzVector p4G2 = myTools->getGammaP4(itTrk2);

			HepLorentzVector p4gg  = p4G1 + p4G2;
			HepLorentzVector p4LPi = p4candidate + p4gg;
			double mLPi  = p4LPi.m();
			double rmLPi = (myTools->getCmsP4() - p4LPi).m();
			double massdiff_this = mLPi - myTools->getMassXi0();

			if(mLPi < 1.1 || mLPi > 1.54) continue;
			if(rmLPi< 1.00 || rmLPi> 1.70) continue;

			if(fabs(massdiff_this) < deltaMass){
				deltaMass = fabs(massdiff_this);
				id1_best = id1_this;
				id2_best = id2_this;
				idL_best = i;
				idpi0_best = ii;
			}
		}
	}
	if(deltaMass == 99.) return StatusCode::SUCCESS;
	Num[4] += 1;


	m_Idshw1 = VIdG1[idpi0_best];
	m_Idshw2 = VIdG2[idpi0_best];



	//==============================
	// save information
	// lambda, pi0 from Xi0
	// otherCharged
	// otherLambda
	// shw
	//==============================

	std::vector<int> iGood;
	iGood.clear();
	int ngcharged = myTools->selectGoodChargedTracks(evtRecEvent, evtRecTrkCol, iGood);
	if(ngcharged <=1 || ngcharged>10) return StatusCode::SUCCESS;
	m_ngcharged = ngcharged;
	m_ncharged  = totalCharged;
	Num[5] += 1;


	//-----------------------------------------
	// information of best Xi0
	//-----------------------------------------

	m_nlvar = 7;
	//lambda
	HepLorentzVector p4L_best = Vp4L[idL_best];
	for(int a=0; a<4; a++) m_p4lambda[a] = p4L_best[a];
	m_p4lambda[4] = id1_best;
	m_p4lambda[5] = id2_best;
	m_p4lambda[6] = Vflavor[idL_best];

	//------------------------------------------
	// lambda in other charged save all of them
	//------------------------------------------
	int notherLambda = 0;
	for(int c =0 ; c<totalCharged; c++){
		EvtRecTrackIterator itTrk1 = evtRecTrkCol->begin() + c;
		int trkId1_this =  (*itTrk1)->trackId();
		if(trkId1_this == id1_best || trkId1_this == id2_best) continue;
		for(int d = c+1; d <totalCharged; d++){
			EvtRecTrackIterator itTrk2 = evtRecTrkCol->begin() + d;
			int trkId2_this =  (*itTrk2)->trackId();
			if(trkId2_this == id1_best || trkId2_this == id2_best) continue;

			LambdaFinder lFinder;
			int findFlag = lFinder.LambdaSelector(c, d, evtRecTrkCol);
			if(findFlag != 1) continue;
			HepLorentzVector p4candidate = lFinder.getP4sec();
			double mass_this = p4candidate.m();
			double dl_this =  lFinder.getdlsec()/lFinder.getdlesec();
			double chiq_sec = lFinder.getchiqsec();
			double massdiff = mass_this - myTools->getMassLambda();
			//
			if(dl_this <= 2.0 ) continue;
			if(chiq_sec >= 200.) continue;
			if(fabs(massdiff) >= 0.03) continue;

			for(int ll=0; ll<4; ll++) m_p4otherLambda[notherLambda][ll] = p4candidate[ll];
			m_p4otherLambda[notherLambda][4] = trkId1_this;
			m_p4otherLambda[notherLambda][5] = trkId2_this;
			notherLambda += 1;
		}
	}
	m_notherLambda = notherLambda;




	//-------------------------------------
	// electron in other charged
	//-------------------------------------
	int ne = 0;
	for(int a=0; a<iGood.size(); a++)
	{
		EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + iGood[a];
		RecMdcKalTrack* mdcKalTrk = (*itTrk)->mdcKalTrack(); 
		if( myTools->isGoodElectron(itTrk) ){
			mdcKalTrk->setPidType(RecMdcKalTrack::electron);
			for ( int ll = 0; ll < 4; ll++ ) m_p4e[ne][ll]=mdcKalTrk->p4(myTools->getMassE() )[ll];
			m_p4e[ne][4]=mdcKalTrk->charge();
			m_p4e[ne][5]=(*itTrk)->trackId();
			ne++;
		}
	}
	m_ne = ne;


	//----------------------
	// information of shw
	// normally three tops in Lambda decay n pi0
	//----------------------


	for(int i=0;i<iGoodGam.size();i++)
	{
		EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + iGoodGam[i];
		HepLorentzVector p4 = myTools->getGammaP4(itTrk);
		for(int a=0; a<4; a++) m_p4shw[i][a] = p4[a];
		m_p4shw[i][4] = (*itTrk)->trackId();
		//tof
		double etof=0;
		if((*itTrk)->isTofTrackValid()){
			SmartRefVector<RecTofTrack> recTofTrackVec=(*itTrk)->tofTrack();
			if(!recTofTrackVec.empty()){
				etof=recTofTrackVec[0]->energy();
			}
			if(etof>100.)etof=0;
		}
		else etof = -9.;
		m_p4shw[i][5] = etof;

	}



	m_tuple1->write();

	return StatusCode::SUCCESS;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

StatusCode Xi0Alg::endRun(){
	MsgStream log(msgSvc(), name());
	log<<MSG::INFO<<"Xi0Alg::endRun()"<<endreq;
	//add your code here
	return StatusCode::SUCCESS;

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

StatusCode Xi0Alg::finalize(){
	MsgStream log(msgSvc(), name());
	std::cout<<"-----------------------------"<<endl;
	std::cout<<"Xi0Alg::finalize()"<<endl;
	for(int a=0; a<6; a++) cout<<Num[a]<<endl;
	std::cout<<"-----------------------------"<<endl;
	return StatusCode::SUCCESS;
}



//--------------------------------------------------------------------------------------------
//--------------------add your code here,for other member-functions---------------------------
//--------------------------------------------------------------------------------------------

//=============================
void Xi0Alg::mc_truth() {
	SmartDataPtr<Event::McParticleCol> mcParticleCol(eventSvc(), "/Event/MC/McParticleCol");

	int m_numParticle = 0;
	bool Decay = false;
	int rootIndex = -1;
	bool strange = false;
	Event::McParticleCol::iterator iter_mc_topo = mcParticleCol->begin();
	for (; iter_mc_topo != mcParticleCol->end(); iter_mc_topo++){
		if ((*iter_mc_topo)->primaryParticle()&&(*iter_mc_topo)->particleProperty()==11&&((*iter_mc_topo)->mother()).particleProperty()==11) {strange=true;}
		if ((*iter_mc_topo)->primaryParticle()) continue;
		if (!(*iter_mc_topo)->decayFromGenerator()) continue;
		if ((*iter_mc_topo)->particleProperty() == 443){
			Decay = true;
			rootIndex = (*iter_mc_topo)->trackIndex();
		}
		if (!Decay) continue;
		int mcidx = ((*iter_mc_topo)->mother()).trackIndex() - rootIndex;
		int pdgid = (*iter_mc_topo)->particleProperty();
		if(strange&&((*iter_mc_topo)->mother()).particleProperty()!=443) mcidx--;
		HepLorentzVector p4iter = (*iter_mc_topo)->initialFourMomentum();
		for(int a=0; a<4; a++) m_p4truth[m_numParticle][a] = p4iter[a];
		m_p4truth[m_numParticle][4] = pdgid * 1.0;
		m_p4truth[m_numParticle][5] = mcidx * 1.0;

		m_numParticle++;
	}
	m_idxmc = m_numParticle;

}


