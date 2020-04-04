#include "HyperonDecayAlg/LambdaFinder.h"

LambdaFinder::LambdaFinder(){

m_chisq_sec = 999;

}
int LambdaFinder::LambdaSelector(int Id1, int Id2, SmartDataPtr<EvtRecTrackCol> evtRecTrkCol ){

	if(Id2 == Id1) cout<<"Error  LambdaXAlg::LambdaFinder Id1 == Id2"<<endl;

	IMessageSvc *msgSvc;
	Gaudi::svcLocator()->service("MessageSvc", msgSvc);
	MsgStream log(msgSvc, "FindLambda");

	IDataProviderSvc* eventSvc = NULL;
	Gaudi::svcLocator()->service("EventDataSvc", eventSvc);

	SmartDataPtr<EvtRecVeeVertexCol> evtRecVeeVertexCol(eventSvc, "/Event/EvtRec/EvtRecVeeVertexCol");
	if ( ! evtRecVeeVertexCol ) {
		log << MSG::INFO<< "Could not find EvtRecVeeVertexCol" << endreq;
		return -1;
	}
	

	// childs to be checked
	EvtRecTrackIterator itTrk_child1 = evtRecTrkCol->begin() + Id1;
	EvtRecTrackIterator itTrk_child2 = evtRecTrkCol->begin() + Id2;
	RecMdcKalTrack* aChild1KalTrk = (*itTrk_child1)->mdcKalTrack(); 
	RecMdcKalTrack* aChild2KalTrk = (*itTrk_child2)->mdcKalTrack(); 

	if (   aChild1KalTrk->charge() * aChild2KalTrk->charge() >= 0   ) return -5;

	//if( ! (isGoodProtonFromLambda(itTrk_child1) || isGoodPionFromLambda(itTrk_child1)  )) return -2;
	//if( ! (isGoodProtonFromLambda(itTrk_child2) || isGoodPionFromLambda(itTrk_child2)  )) return -2;
	
	int Np(0), Npi(0);
	if( isGoodProtonFromLambda(itTrk_child1) ) Np++;
	if( isGoodProtonFromLambda(itTrk_child2) ) Np++;
	if( isGoodPionFromLambda(itTrk_child1)) Npi++;
	if( isGoodPionFromLambda(itTrk_child2) ) Npi++;


	int TrkId1 = (*itTrk_child1)->trackId();
	int TrkId2 = (*itTrk_child2)->trackId();
	vector<int> VchildId;	VchildId.clear();
	VchildId.push_back(TrkId1);
	VchildId.push_back(TrkId2);




	bool findVee = false;


	if(Np != 1  || Npi == 0 ) return -2;

	//Vee 
	int vertexID;
	for(EvtRecVeeVertexCol::iterator lambdaItr = evtRecVeeVertexCol->begin(); lambdaItr < evtRecVeeVertexCol->end(); lambdaItr++){

		// Lambda 3122  -> p pi-
		// Alambda -3122 -> pbar pi+
		int vID = (*lambdaItr)->vertexId();
		if( fabs(vID) != 3122) continue;



		int Child1TrkId = ((*lambdaItr)->daughter(0))->trackId();
		int Child2TrkId = ((*lambdaItr)->daughter(1) )->trackId();


		if( InVector(Child1TrkId, VchildId)==false  ) continue;
		if( InVector(Child2TrkId, VchildId)==false  ) continue;

		findVee = true;

	}


	if(findVee == false) return -3;

	//second vertex 
	Hep3Vector xorigin(0,0,0);
	Hep3Vector sigv(0,0,0);

	IVertexDbSvc*  vtxsvc;
	Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
	if(vtxsvc->isVertexValid()){
		double* dbv = vtxsvc->PrimaryVertex();
		double*  vv = vtxsvc->SigmaPrimaryVertex();

		sigv.setX(vv[0]);
		sigv.setY(vv[1]);
		sigv.setZ(vv[2]);

		xorigin.setX(dbv[0]);
		xorigin.setY(dbv[1]);
		xorigin.setZ(dbv[2]);
	}
	///for vertex fit
	HepPoint3D vx(0., 0., 0.);
	HepSymMatrix Evx(3, 0);
	double bx = 1E+6;
	double by = 1E+6;
	double bz = 1E+6;
	Evx[0][0] = bx*bx;
	Evx[1][1] = by*by;
	Evx[2][2] = bz*bz;

	VertexParameter vpar;
	vpar.setVx(vx);
	vpar.setEvx(Evx);
	///for second vertexfit
	HepPoint3D IP(xorigin[0],xorigin[1],xorigin[2]);

	HepSymMatrix IPE(3, 0);
	double bx2 = sigv[0];
	double by2 = sigv[1];
	double bz2 = sigv[2];
	IPE[0][0] = bx2*bx2;
	IPE[1][1] = by2*by2;
	IPE[2][2] = bz2*bz2;

	VertexParameter birth;
	birth.setVx(IP);
	birth.setEvx(IPE);

	VertexFit *vtxfit = VertexFit::instance();
	SecondVertexFit *lambdafit = SecondVertexFit::instance();



	// should not assign m_flavor based on vertexID.
	// candidate from trk a and b could appear as +-3122 at the same time
	// use proton paticleID is better than that of pion
	WTrackParameter wptrk_proton, wptrk_pion;
	if(isGoodProtonFromLambda(itTrk_child1)){
		setProtonProb(itTrk_child1);
		aChild1KalTrk->setPidType(RecMdcKalTrack::proton);
		wptrk_proton = WTrackParameter(xmass[4], aChild1KalTrk->helix(), aChild1KalTrk->err());
		if(aChild1KalTrk->charge() > 0) m_flavor = 1;
		else if(aChild1KalTrk->charge() < 0) m_flavor = -1;
		else cout<<"wrong type charge proton track"<<endl;

		aChild2KalTrk->setPidType(RecMdcKalTrack::pion);
		wptrk_pion = WTrackParameter(xmass[2], aChild2KalTrk->helix(), aChild2KalTrk->err());

	}else{
		setProtonProb(itTrk_child2);
		aChild2KalTrk->setPidType(RecMdcKalTrack::proton);
		wptrk_proton = WTrackParameter(xmass[4], aChild2KalTrk->helix(), aChild2KalTrk->err());
		if(aChild2KalTrk->charge() > 0) m_flavor = 1;
		else if(aChild2KalTrk->charge() < 0) m_flavor = -1;
		else cout<<"wrong type charge proton track"<<endl;

		aChild1KalTrk->setPidType(RecMdcKalTrack::pion);
		wptrk_pion = WTrackParameter(xmass[2], aChild1KalTrk->helix(), aChild1KalTrk->err());
	}

	//proton
	WTrackParameter wpi1trk(wptrk_proton);
	//pion
	WTrackParameter wpi2trk(wptrk_pion);

	vtxfit->init();
	vtxfit->AddTrack(0,wpi1trk);
	vtxfit->AddTrack(1,wpi2trk);
	vtxfit->AddVertex(0,vpar,0,1);
	bool okvtxfit = vtxfit->Fit(0);
	if(!okvtxfit) return -4;
	vtxfit->Swim(0);
	vtxfit->BuildVirtualParticle(0);
	WTrackParameter lambdaTrk = vtxfit->wVirtualTrack(0);


	lambdafit->init();
	lambdafit->AddTrack(0,lambdaTrk);
	lambdafit->setVpar(vtxfit->vpar(0));
	lambdafit->setPrimaryVertex(birth);
	lambdafit->Fit();
	double vtxchi = vtxfit->chisq(0);
	if(vtxchi> 100.) return -4;



	double svchi = lambdafit->chisq();

	p4lambda_se=lambdafit->p4par();//after second vertexFit
	m_dl_sec = lambdafit->decayLength();
	m_dle_sec = lambdafit->decayLengthError();
	HepLorentzVector lambda_sv = lambdafit->p4par();
	m_mass_sec = lambda_sv.m();


	HepLorentzVector p4_lambda_sec;
	p4_lambda_sec =( lambdafit->wpar() ).p();

	//cout<<"lambda mass previous "<<m_mass_sec<<"  new  "<<p4_lambda_sec.m()<<endl;


	m_chisq_sec = svchi;


	return 1;

}
bool LambdaFinder::InVector(int cand,   vector<int> &vint)
{
	bool flag = false;
	for(int a=0; a<vint.size(); a++){
		if(vint[a] == cand){ flag = true;break;}
	}
	return flag;
}

bool LambdaFinder::isGoodProtonFromLambda(EvtRecTrackIterator itTrk){
	//IP distance
	CLHEP::Hep3Vector xorigin(0,0,0);
	IVertexDbSvc*  vtxsvc;
	Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
	if(vtxsvc->isVertexValid()){
		double *dbv = vtxsvc->PrimaryVertex(); 
		xorigin.setX(dbv[0]);
		xorigin.setY(dbv[1]);
		xorigin.setZ(dbv[2]);
	}

	if(!(*itTrk)->isMdcKalTrackValid()) return false;
	if(!(*itTrk)->isMdcTrackValid()) return false;

	RecMdcKalTrack* mdcTrk = (*itTrk)->mdcKalTrack();

	HepVector a = mdcTrk->helix();
	HepSymMatrix Ea = mdcTrk->err();
	HepPoint3D point0(0.,0.,0.);

	VFHelix helixip(point0,a,Ea);
	HepPoint3D IP(xorigin[0],xorigin[1],xorigin[2]);
	helixip.pivot(IP);
	HepVector vecipa = helixip.a();

	double vz0 = vecipa[3];
	double vr0 = vecipa[0];

	if(fabs(vz0) >= 20.) return false;//
	if(fabs(cos(mdcTrk->theta())) > 0.93) return false;

	ParticleID * pidp = ParticleID::instance();
	pidp->init();
	pidp->setMethod(pidp->methodProbability());
	pidp->setChiMinCut(4);
	pidp->setRecTrack(*itTrk);
	// use PID sub-system
	pidp->usePidSys(pidp->useDedx() | pidp->useTof1() | pidp->useTof2());
	pidp->identify(pidp->onlyPion() | pidp->onlyKaon() | pidp->onlyProton());
	pidp->calculate();

	if(pidp->IsPidInfoValid()) {
		double probpi = pidp->probPion();
		double probk  = pidp->probKaon();
		double probp  = pidp ->probProton();
		if(probp > probpi && probp > 0.0 && probp > probk){
		   	return true;
		}
		else
			return false;
	}
	else
		return false;

}


bool LambdaFinder::isGoodPionFromLambda(EvtRecTrackIterator itTrk){
	//IP distance
	CLHEP::Hep3Vector xorigin(0,0,0);
	IVertexDbSvc*  vtxsvc;
	Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
	if(vtxsvc->isVertexValid()){
		double *dbv = vtxsvc->PrimaryVertex(); 
		xorigin.setX(dbv[0]);
		xorigin.setY(dbv[1]);
		xorigin.setZ(dbv[2]);
	}

	if(!(*itTrk)->isMdcKalTrackValid()) return false;
	if(!(*itTrk)->isMdcTrackValid()) return false;

	RecMdcKalTrack* mdcTrk = (*itTrk)->mdcKalTrack();

	HepVector a = mdcTrk->helix();
	HepSymMatrix Ea = mdcTrk->err();
	HepPoint3D point0(0.,0.,0.);

	VFHelix helixip(point0,a,Ea);
	HepPoint3D IP(xorigin[0],xorigin[1],xorigin[2]);
	helixip.pivot(IP);
	HepVector vecipa = helixip.a();

	double vz0 = vecipa[3];
	double vr0 = vecipa[0];

	if(fabs(vz0) >= 20.) return false;//
	if(fabs(cos(mdcTrk->theta())) > 0.93) return false;

	return true;

}

double LambdaFinder::setProtonProb(EvtRecTrackIterator itTrk){

	m_probp = -9.;
	ParticleID * pidp = ParticleID::instance();
	pidp->init();
	pidp->setMethod(pidp->methodProbability());
	pidp->setChiMinCut(4);
	pidp->setRecTrack(*itTrk);
	// use PID sub-system
	pidp->usePidSys(pidp->useDedx() | pidp->useTof1() | pidp->useTof2());
	pidp->identify(pidp->onlyPion() | pidp->onlyKaon() | pidp->onlyProton());
	pidp->calculate();

	if(pidp->IsPidInfoValid()) {
		double probpi = pidp->probPion();
		double probk  = pidp->probKaon();
		double probp  = pidp ->probProton();
		if(probp > probpi && probp > 0.0 && probp > probk){
		   	return true;
			m_probp = probp;
		}
		else
			return false;
	}
	else
		return false;

}
