#include "HyperonDecayAlg/MyTools.h"

MyTools::MyTools(){
}

double MyTools::getMassE(){return  0.000511;}
double MyTools::getMassMu(){return 0.105658;}
double MyTools::getMassPi(){return 0.139570;}
double MyTools::getMassK(){return 0.493677;}
double MyTools::getMassP(){return 0.938272;}
double MyTools::getMassLambda(){return 1115.683*0.001;}
double MyTools::getMassSigma0(){return 1192.642*0.001;}
double MyTools::getMassSigmaPlus(){return 1189.37*0.001;}
double MyTools::getMassSigmaMinus(){return 1197.449*0.001;}
double MyTools::getMassSigma1385Minus(){return 1387.2*0.001; }
double MyTools::getMassXiminus(){return 1321.71*0.001;}
double MyTools::getMassXi0(){return 1314.86*0.001;}

bool MyTools::isInVector(vector<int> V, int id){
	bool status = false;
	if(V.size() == 0) status = false;
	else{
		for(int a=0; a<V.size(); a++)
		{
			if(id == V[a]){
				status = true;
				break;
			}
		}
	}
	return status;
}


HepLorentzVector MyTools::getCmsP4(){
	HepLorentzVector p4_cms(0.011*3.097 ,0.,0., 3.097);
	return p4_cms;
}

HepLorentzVector MyTools::getGammaP4(const RecEmcShower* gTrk, Hep3Vector origin)
{
	Hep3Vector Gm_Vec(gTrk->x(), gTrk->y(), gTrk->z());
	Hep3Vector Gm_Mom = Gm_Vec - origin;
	Gm_Mom.setMag(gTrk->energy());
	HepLorentzVector pGm(Gm_Mom, gTrk->energy());
	return pGm;
}




HepLorentzVector MyTools::getGammaP4(EvtRecTrackIterator itTrk)
{
	RecEmcShower* emcTrk = (*itTrk)->emcShower();
	double eraw = emcTrk->energy();
	double phi = emcTrk->phi();
	double theta = emcTrk->theta();
	HepLorentzVector p4 = HepLorentzVector(eraw * sin(theta) * cos(phi), eraw * sin(theta) * sin(phi),eraw * cos(theta),eraw );
	return p4;
}



void MyTools::selectNeutralTracks(SmartDataPtr<EvtRecEvent> evtRecEvent,
		SmartDataPtr<EvtRecTrackCol> evtRecTrkCol,  vector<int> &iGam) {


	for(int i=evtRecEvent->totalCharged(); i< evtRecEvent->totalTracks(); i++) {
		if (i > 20) break;

		EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + i ;
		if(!(*itTrk)->isEmcShowerValid()) continue;
		RecEmcShower *emcTrk = (*itTrk)->emcShower();

		// TDC window
		if ( !(emcTrk->time() >= 0. && emcTrk->time() <= 14) )
			continue; 

		// Energy threshold
		double abs_costheta(fabs(cos(emcTrk->theta())));
		bool barrel = (abs_costheta < 0.8); 
		bool endcap = (abs_costheta > 0.86
				&& abs_costheta < 0.92);
		double eraw = emcTrk->energy();

		if (true){     // Cut by "costheta"
			if ( !( (barrel && eraw > 0.025)
						|| (endcap && eraw > 0.050)))  continue; 
		}
		else{                      // Cut by "module"
			int module = emcTrk->module();
			if( module == 1 ){  if( !(eraw > 0.025) ) continue; }
			else{ if( !(eraw > 0.050) ) continue; }
		}

		// photon isolation: the opening angle between a candidate shower
		// and the closest charged track should be larger than 10 degree 
		CLHEP::Hep3Vector emcpos(emcTrk->x(), emcTrk->y(), emcTrk->z());

		// EMC costheta cut 
		double costhe = cos(emcpos.theta());
		if ( fabs(costhe) >= 0.93) continue;

		// find the nearest charged track
		double dthe = 200.;
		double dphi = 200.;
		double dang = 200.; 
		for(int j = 0; j < evtRecEvent->totalCharged(); j++) {
			EvtRecTrackIterator jtTrk = evtRecTrkCol->begin() + j;
			if(!(*jtTrk)->isExtTrackValid()) continue;
			RecExtTrack *extTrk = (*jtTrk)->extTrack();
			if(extTrk->emcVolumeNumber() == -1) continue;
			CLHEP::Hep3Vector extpos = extTrk->emcPosition();
			double angd = extpos.angle(emcpos);
			double thed = extpos.theta() - emcpos.theta();
			double phid = extpos.deltaPhi(emcpos);
			thed = fmod(thed+CLHEP::twopi+CLHEP::twopi+pi, CLHEP::twopi) - CLHEP::pi;
			phid = fmod(phid+CLHEP::twopi+CLHEP::twopi+pi, CLHEP::twopi) - CLHEP::pi;

			if(fabs(thed) < fabs(dthe)) dthe = thed;
			if(fabs(phid) < fabs(dphi)) dphi = phid;
			if(angd < dang) dang = angd;	    
		}

		if(dang>=200) continue;
		dthe = dthe * 180 / (CLHEP::pi);
		dphi = dphi * 180 / (CLHEP::pi);
		dang = dang * 180 / (CLHEP::pi);
		if (dang < 20 ) continue; 

		iGam.push_back((*itTrk)->trackId());
		//cout<<"check GAMMA trackId "<<(*itTrk)->trackId()<<" loop index number "<<i<<endl;
	} // end loop neutral tracks     
}


bool MyTools::isGoodProton(EvtRecTrackIterator itTrk){
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
		if(probp > probpi && probp > 0.0 && probp > probk) return true;
		else
			return false;
	}
	else
		return false;
}

bool MyTools::isGoodPion(EvtRecTrackIterator itTrk){
	//pi particle identification
	ParticleID * pidp = ParticleID::instance();
	pidp->init();
	pidp->setMethod(pidp->methodProbability());
	pidp->setChiMinCut(4);
	pidp->setRecTrack(*itTrk);
	// use PID sub-system
	pidp->usePidSys(pidp->useDedx() | pidp->useTof1() | pidp->useTof2());
	pidp->identify(pidp->onlyPionKaon());
	pidp->calculate();
	if(pidp->IsPidInfoValid()) {
		double probpi = pidp->probPion();
		double probk  = pidp->probKaon();
		if(probpi > probk && probpi > 0.00) return true;
		else
			return false;
	}
	else
		return false;
}

bool MyTools::isGoodElectron(EvtRecTrackIterator itTrk){
	ParticleID * pidp = ParticleID::instance();
	pidp->init();
	pidp->setMethod(pidp->methodProbability());
	pidp->setChiMinCut(4);
	pidp->setRecTrack(*itTrk);
	// use PID sub-system
	pidp->usePidSys(pidp->useDedx() | pidp->useTof1() | pidp->useTof2());
	pidp->identify(pidp->onlyPion() | pidp->onlyKaon() | pidp->onlyElectron());
	pidp->calculate();

	if(pidp->IsPidInfoValid()) {
		double probpi = pidp->probPion();
		double probk  = pidp->probKaon();
		double probe  = pidp->probElectron();
		if( probe > probpi  && probe > 0.0 && probe > probk && probe>0.8*(probe + probpi +  probk) ) return true;
		else
			return false;
	}
	else
		return false;
}

bool MyTools::isGoodMuon(EvtRecTrackIterator itTrk){
	ParticleID * pidp = ParticleID::instance();
	pidp->init();
	pidp->setMethod(pidp->methodProbability());
	pidp->setChiMinCut(4);
	pidp->setRecTrack(*itTrk);
	// use PID sub-system
	pidp->usePidSys(pidp->useDedx() | pidp->useTof1() | pidp->useTof2());
	//pidp->identify(pidp->onlyPion() | pidp->onlyKaon() | pidp->onlyProton());
	//pidp->identify(pidp->onlyElectron() | pidp->onlyMuon());
	//pidp->calculate();

	//if(pidp->IsPidInfoValid()) {
	//	double probpi = pidp->probPion();
	//	double probk  = pidp->probKaon();
	//	double probe  = pidp->probElectron();
	//	double probmu  = pidp->probMuon();
	//	if(probmu > probe && probmu > 0.00 && probmu > probk) return true;
	//	else
	//		return false;
	//}
	//else
	return false;
}

int MyTools::selectGoodChargedTracks(SmartDataPtr<EvtRecEvent> evtRecEvent,
		SmartDataPtr<EvtRecTrackCol> evtRecTrkCol,
		std::vector<int> & iGood) {

	CLHEP::Hep3Vector xorigin(0,0,0);
	IVertexDbSvc*  vtxsvc;
	Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
	if(vtxsvc->isVertexValid()){
		double *dbv = vtxsvc->PrimaryVertex(); 
		xorigin.setX(dbv[0]);
		xorigin.setY(dbv[1]);
		xorigin.setZ(dbv[2]);
	}

	iGood.clear();
	int np=0;
	int nm=0;

	for(int i = 0; i < evtRecEvent->totalCharged(); i++){
		EvtRecTrackIterator itTrk=evtRecTrkCol->begin() + i;
		if(!(*itTrk)->isMdcKalTrackValid()) continue;
		if(!(*itTrk)->isMdcTrackValid()) continue;
		RecMdcKalTrack* mdcTrk = (*itTrk)->mdcKalTrack();

		if (!passVertexSelection(xorigin, mdcTrk) ) continue; 
		if(fabs(cos(mdcTrk->theta())) > 0.93) continue;

		iGood.push_back(i);
		//cout<<"check charged trackId "<<(*itTrk)->trackId()<<" loop index number "<<i<<endl;

	} // end charged tracks
	return iGood.size();
}


bool MyTools::passVertexSelection(CLHEP::Hep3Vector xorigin,
		RecMdcKalTrack* mdcTrk ) {
	HepVector a = mdcTrk->helix();
	HepSymMatrix Ea = mdcTrk->err();
	HepPoint3D point0(0.,0.,0.);

	VFHelix helixip(point0,a,Ea);
	HepPoint3D IP(xorigin[0],xorigin[1],xorigin[2]);
	helixip.pivot(IP);
	HepVector vecipa = helixip.a();

	double m_vz0 = vecipa[3];

	if(fabs(m_vz0) >= 20.) return false;
	//if(fabs(m_vr0) >= m_vr0cut) return false;

	return true;
}

