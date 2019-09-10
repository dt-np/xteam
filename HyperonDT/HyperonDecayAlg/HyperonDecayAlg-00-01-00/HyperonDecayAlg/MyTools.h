#ifndef MYTOOLS_Header
#define MYTOOLS_Header

#include "GaudiKernel/Algorithm.h"
#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/SmartDataPtr.h"
#include "GaudiKernel/IDataProviderSvc.h"
#include "GaudiKernel/PropertyMgr.h"
#include "GaudiKernel/SmartRefVector.h"

#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "EvtRecEvent/EvtRecVeeVertex.h"

#include "VertexFit/IVertexDbSvc.h"
#include "VertexFit/VertexFit.h"
#include "VertexFit/SecondVertexFit.h"
#include "VertexFit/KinematicFit.h"
#include "VertexFit/Helix.h"

#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/TwoVector.h"
#include "CLHEP/Geometry/Point3D.h"

#include "ParticleID/ParticleID.h"

using CLHEP::Hep3Vector;
using CLHEP::Hep2Vector;
using CLHEP::HepLorentzVector;




using CLHEP::HepLorentzVector;



class MyTools
{

	public:
		MyTools(void);
		~MyTools(void){};

		HepLorentzVector getGammaP4(const RecEmcShower* gTrk, Hep3Vector origin);
		HepLorentzVector getGammaP4(EvtRecTrackIterator itTrk);
		double getMassE(); 
		double getMassMu();
		double getMassPi();
		double getMassK(); 
		double getMassP(); 
		double getMassLambda();
		double getMassSigma0();
		double getMassSigmaPlus();
		double getMassSigmaMinus();
		double getMassSigma1385Minus();
		double getMassXiminus();
		double getMassXi0();
		bool isInVector(vector<int>, int);

		HepLorentzVector getCmsP4();

		void selectNeutralTracks(SmartDataPtr<EvtRecEvent> evtRecEvent, SmartDataPtr<EvtRecTrackCol> evtRecTrkCol,  vector<int> &iGam);
		int  selectGoodChargedTracks(SmartDataPtr<EvtRecEvent> evtRecEvent, SmartDataPtr<EvtRecTrackCol> evtRecTrkCol, 	std::vector<int> & iGood);

		bool isGoodProton(EvtRecTrackIterator itTrk);
		bool isGoodPion(EvtRecTrackIterator itTrk);
		bool isGoodElectron(EvtRecTrackIterator itTrk);
		bool isGoodMuon(EvtRecTrackIterator itTrk);
		bool passVertexSelection(CLHEP::Hep3Vector xorigin, RecMdcKalTrack* mdcTrk );

	private:
};


#endif
