#ifndef LambdaFinder_Header
#define LambdaFinder_Header
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

using CLHEP::Hep3Vector;
using CLHEP::Hep2Vector;
using CLHEP::HepLorentzVector;

#include "ParticleID/ParticleID.h"

const double xmass[5] = {0.000511, 0.105658, 0.139570,0.493677, 0.938272};//e,mu,pi,k,p
using CLHEP::HepLorentzVector;


class LambdaFinder
{
	public:
		LambdaFinder(void);
		~LambdaFinder(void){};


		int LambdaSelector(int Id1, int Id2, SmartDataPtr<EvtRecTrackCol> evtRecTrkCol);
		bool InVector(int, vector<int>&);


		HepLorentzVector getP4sec(){return p4lambda_se;};
		double           getdlsec(){return m_dl_sec;};
		double			 getdlesec(){return m_dle_sec;};
		double		     getchiqsec(){return m_chisq_sec;};
		int				 getFlavorFlag(){return  m_flavor;};// 1 lambda, -1 lambdabar
		double			 getProbp(){return m_probp;};

		bool             isGoodProtonFromLambda(EvtRecTrackIterator itTrk);
		bool             isGoodPionFromLambda(EvtRecTrackIterator itTrk);
		double           setProtonProb(EvtRecTrackIterator itTrk);

	private:
		double m_dl_sec, m_dle_sec;
		double m_chisq_sec;
		double m_mass_sec;
		double m_probp;
		int	   m_flavor;
		HepLorentzVector p4lambda_se;
};
#endif
