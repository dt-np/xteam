#ifndef Xi0Alg_Header
#define Xi0Alg_Header

#include "GaudiKernel/Algorithm.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/TwoVector.h"
#include "CLHEP/Geometry/Point3D.h"
#include "McTruth/McParticle.h"
#include <vector>
using CLHEP::Hep3Vector;
using CLHEP::Hep2Vector;
using CLHEP::HepLorentzVector;
using Event::McParticle;

#include "ParticleID/ParticleID.h"
#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "VertexFit/IVertexDbSvc.h"
#include "VertexFit/VertexFit.h"
#include "VertexFit/KinematicFit.h"
#include "VertexFit/Helix.h"
typedef std::vector<WTrackParameter> VWTrkPara;

#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/SmartDataPtr.h"
#include "GaudiKernel/IDataProviderSvc.h"
#include "GaudiKernel/PropertyMgr.h"
#include "GaudiKernel/SmartRefVector.h"

#include "EventModel/EventModel.h"
#include "EventModel/Event.h"
#include "EventModel/EventHeader.h"

#include "EvtRecEvent/EvtRecDTag.h"
#include "EvtRecEvent/EvtRecVeeVertex.h"
#include "EvtRecEvent/EvtRecPi0.h"
#include "DstEvent/TofHitStatus.h"

#include "TMath.h"
#include "GaudiKernel/INTupleSvc.h"
#include "GaudiKernel/NTuple.h"
#include "GaudiKernel/Bootstrap.h"
#include "GaudiKernel/IHistogramSvc.h"

#include "EvTimeEvent/RecEsTime.h"
#include "MdcRecEvent/RecMdcKalTrack.h"


//
//namespace
//
class Xi0Alg:public Algorithm {
  public:
    Xi0Alg(const std::string& name, ISvcLocator* pSvcLocator);
    ~Xi0Alg();
    StatusCode initialize();
    StatusCode beginRun();   
    StatusCode execute();
    StatusCode endRun();
    StatusCode finalize();

	void mc_truth();




  private:

	long Num[6];
	bool m_saveMcTruth;


	NTuple::Tuple* m_tuple1;
	NTuple::Item<int> m_run, m_event;
	NTuple::Item<int> m_idxmc;
	//0-3 : p4; 4: pdgid; 5: motheridx
	NTuple::Matrix<double> m_p4truth;

	NTuple::Item<int> m_ngcharged, m_ngshower, m_ncharged, m_nshower;
	NTuple::Matrix<double>  m_p4shw, m_p4charged;

	NTuple::Item<int> m_ne, m_np;
	//0,3 p4; 4 charge;
	NTuple::Matrix<double> m_p4e, m_p4p, m_p4otherLambda; 

	NTuple::Item<int> m_nlambda, m_nlvar, m_notherLambda, m_Idshw1, m_Idshw2;
	//momentum from secondary vertex fit 0,3 ; chiq 4; L/sigma 5; lambda/lambdabar 6, take as +-1; 7,8 charged trackId ; 9 gam trackId
	NTuple::Array<double> m_p4lambda, m_p4pi;


};

//add your inline methods
//?

#endif//Xi0Alg_Header
