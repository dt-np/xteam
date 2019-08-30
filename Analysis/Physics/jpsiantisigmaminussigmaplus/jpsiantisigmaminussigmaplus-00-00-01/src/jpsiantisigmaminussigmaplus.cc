// -*- C++ -*- //
//
// Description: J/psi   ->  antisigmaminus  sigmaplus
//
// Original Author:  Amit pathak <amitraahul@itp.ac.cn>
//         Created:  [2019-05-17 Fri 14:30] 
//         Inspired by SHI Xin's code 
         

// system include files
//


#include "GaudiKernel/Algorithm.h"
#include "GaudiKernel/DeclareFactoryEntries.h"
#include "GaudiKernel/LoadFactoryEntries.h"
#include "GaudiKernel/NTuple.h"
#include "GaudiKernel/Bootstrap.h"

#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"

#include "EventModel/EventHeader.h"
#include "EventModel/EventModel.h"
#include "EventModel/Event.h"
#include "TrigEvent/TrigEvent.h"
#include "TrigEvent/TrigData.h"

#include "CLHEP/Vector/ThreeVector.h"

#include "DstEvent/TofHitStatus.h"

#include "VertexFit/IVertexDbSvc.h"
#include "VertexFit/Helix.h"
#include "VertexFit/WTrackParameter.h"
#include "VertexFit/VertexFit.h"

#include "ParticleID/ParticleID.h"
#include "McTruth/McParticle.h"

#include "VertexFit/KalmanKinematicFit.h"

#include <TFile.h>
#include <TH1.h>
#include <TTree.h>
//
// class declaration 
//

class jpsiantisigmaminussigmaplus : public Algorithm {
  
public:
  jpsiantisigmaminussigmaplus(const std::string&, ISvcLocator*);
  ~jpsiantisigmaminussigmaplus(); 
  StatusCode initialize();
  StatusCode execute();
  StatusCode finalize();

private:

double m_ecms;
double m_vr0cut, m_vz0cut;
double m_cha_costheta_cut;
double m_total_number_of_charged_max;
double m_min_emctime;
double m_max_emctime;
double m_gammaCosCut;
double m_costheta_barrel_max;
double m_costheta_endcap_min;
double m_costheta_endcap_max;
double m_energy_barrel_min;
double m_energy_endcap_min;
double m_photon_iso_angle_min;
//double m_proton_polar_angle_max;//Pion has been chnaged by proton
//double m_proton_momentum_max;// pion has been changed by proton
double m_diproton_mass_min; 
double m_diproton_mass_max;
double m_prob_proton_min; //changed with proton according to invisible code in which pion min was defined
double m_prpr_costheta_max;
double m_prprsys_costheta_max; 

//output file
std::string m_output_filename;
bool m_isMonteCarlo; 
bool m_eventrate;
bool m_isZCcondition;
TFile* m_fout; 


//define Histograms
TH1F* h_evtflw;


//define Trees
TTree* m_tree;

//common info
int m_run;
int m_event;

//
//charged tracks
//
int m_ncharged;
int m_nptrk;
int m_nmtrk;
double m_trkp_p; 
double m_trkp_px; 
double m_trkp_py; 
double m_trkp_pz; 
double m_trkp_theta; 
double m_trkp_phi; 
double m_trkp_eraw; 
  
double m_trkm_p; 
double m_trkm_px; 
double m_trkm_py; 
double m_trkm_pz; 
double m_trkm_theta; 
double m_trkm_phi; 
double m_trkm_eraw;

// neutral tracks
int m_nshow;
int m_ngam;
std::vector<double> *m_raw_gpx; 
std::vector<double> *m_raw_gpy; 
std::vector<double> *m_raw_gpz; 
std::vector<double> *m_raw_ge; 

std::vector<double> *m_raw_phi;
std::vector<double> *m_raw_theta;
std::vector<double> *m_raw_costheta;
std::vector<int> *m_raw_cstat;
std::vector<int> *m_raw_nhit;       
std::vector<int> *m_raw_module;
std::vector<double> *m_raw_secmom;
std::vector<double> *m_raw_time; 
//jpsiantisigmaminussigmaplus
int m_ntrk;

// vertex 
double m_vr0;
double m_vz0;


// PID info
double m_prob_pip;
double m_prob_pim;
double m_prob_kp;
double m_prob_km;
double m_prob_p;
double m_prob_pb;

// proton info
double m_prp_px;
double m_prp_py;
double m_prp_pz;

double m_prm_px;
double m_prm_py;
double m_prm_pz;

// digamma invariant mass
double m_kmfit_mass;
double m_kmfit_energy1;
double m_kmfit_energy2;

//
//functions
//
void book_histogram();
void book_tree();
void clearVariables();
bool buildjpsiantisigmaminussigmaplus();
void saveTrkInfo(EvtRecTrackIterator);
void saveProtonInfo(RecMdcKalTrack *);
int selectChargedTracks(SmartDataPtr<EvtRecEvent>,
	  SmartDataPtr<EvtRecTrackCol>,
	  std::vector<int> &);
int selectProton(SmartDataPtr<EvtRecTrackCol>,
    std::vector<int>);
int selectNeutralTracks(SmartDataPtr<EvtRecEvent>,
		                  SmartDataPtr<EvtRecTrackCol>,
                      std::vector<int>&);
void saveGamInfo(std::vector<int>,
		SmartDataPtr<EvtRecTrackCol>);
void calcTrackPID(EvtRecTrackIterator,
		double&,
		double&,
		double&);
int kinematicFit(SmartDataPtr<EvtRecTrackCol> evtRecTrkCol,
		std::vector<int>);
void saveKinematicFitInfo(HepLorentzVector,HepLorentzVector);
bool passVertexSelection(CLHEP::Hep3Vector,
		RecMdcKalTrack* ); 
CLHEP::Hep3Vector getOrigin();
};


//
//module declare 
//


DECLARE_ALGORITHM_FACTORY( jpsiantisigmaminussigmaplus )
DECLARE_FACTORY_ENTRIES( jpsiantisigmaminussigmaplus ) {
  DECLARE_ALGORITHM(jpsiantisigmaminussigmaplus);
}

LOAD_FACTORY_ENTRIES( jpsiantisigmaminussigmaplus )
//
// constants
//

const double PROTON_MASS = 0.938272;

const int ELECTRON_PDG_ID = 11;
const int MUON_PDG_ID = 13;
const int PIONPLUS_PDG_ID = 211;

const int JPSI_PDG_ID = 443;
const int PSI2S_PDG_ID = 100443;
const int PROTON_PDG_ID = 2212; 
const int NEUTRON_PDG_ID = 2112; 

//
//member functions
//


jpsiantisigmaminussigmaplus::jpsiantisigmaminussigmaplus(const std::string& name, ISvcLocator* pSvcLocator) :
  Algorithm(name, pSvcLocator),
m_tree(0),
m_raw_gpx(0), 
m_raw_gpy(0), 
m_raw_gpz(0), 
m_raw_ge(0),  
m_raw_phi(0),
m_raw_theta(0),
m_raw_costheta(0),
m_raw_cstat(0),
m_raw_nhit(0),
m_raw_module(0),
m_raw_secmom(0),
m_raw_time(0)
{
declareProperty("OutputFileName",m_output_filename);
declareProperty("IsMonteCarlo",m_isMonteCarlo);
declareProperty("ZChi_AnaCondition", m_isZCcondition=false);
declareProperty("Ecms", m_ecms = 3.097);
declareProperty("Vr0cut", m_vr0cut=2.0);
declareProperty("Vz0cut", m_vz0cut=10.0);
declareProperty("ChaCosthetaCut", m_cha_costheta_cut=0.93);
declareProperty("TotalNumberOfChargedMax", m_total_number_of_charged_max=50);
declareProperty("MinEstCut", m_min_emctime=0.0);
declareProperty("MaxEstCut", m_max_emctime=14.0);
declareProperty("GammaCosCut",  m_gammaCosCut= 0.93); 
declareProperty("CosthetaBarrelMax", m_costheta_barrel_max=0.8);
declareProperty("CosthetaEndcapMin", m_costheta_endcap_min=0.86);
declareProperty("CosthetaEndcapMax", m_costheta_endcap_max=0.92);
declareProperty("EnergyBarrelMin", m_energy_barrel_min=0.025); 
declareProperty("EnergyEndcapMin", m_energy_endcap_min=0.050);
declareProperty("PhotonIsoAngleMin", m_photon_iso_angle_min=20.0);
declareProperty("ProbProtonMin", m_prob_proton_min=0.001);
declareProperty("DiprotonMassMin", m_diproton_mass_min=3.0);
declareProperty("DiprotonMassMax", m_diproton_mass_max=3.2);
declareProperty("PrPrCosthetaMax", m_prpr_costheta_max=0.99);
declareProperty("PrPrSysCosthetaMax", m_prprsys_costheta_max=0.99);
}

StatusCode jpsiantisigmaminussigmaplus::initialize(){ MsgStream log(msgSvc(), name());
 log << MSG::INFO << ">>>>>>> in initialize()" << endmsg;

  StatusCode status;
  
  m_fout = new TFile(m_output_filename.c_str(), "RECREATE");
  m_fout->cd(); 

  book_histogram(); 
  book_tree(); 

  log << MSG::INFO << "successfully return from initialize()" <<endmsg; 

 return StatusCode::SUCCESS;
}


StatusCode jpsiantisigmaminussigmaplus::execute() {
 MsgStream log(msgSvc(), name());
  log << MSG::INFO << "in execute()" << endreq;
  
  // clear variables 
   clearVariables();
   h_evtflw->Fill(0); //raw
SmartDataPtr<Event::EventHeader> eventHeader(eventSvc(),"/Event/EventHeader");
if (!eventHeader) return StatusCode::FAILURE;

       
m_run = eventHeader->runNumber();
m_event = eventHeader->eventNumber();

if (buildjpsiantisigmaminussigmaplus()) {
m_tree->Fill();// only fill tree for the selected events 
}

return StatusCode::SUCCESS; 
}

StatusCode jpsiantisigmaminussigmaplus::finalize() {
MsgStream log(msgSvc(), name());
log << MSG::INFO << "in finalize()" << endmsg;

m_fout->cd();
m_tree->Write();
h_evtflw->Write();
m_fout->Close();

return StatusCode::SUCCESS;
}


jpsiantisigmaminussigmaplus::~jpsiantisigmaminussigmaplus() {
}

void jpsiantisigmaminussigmaplus::book_histogram() {

h_evtflw = new TH1F("hevtflw","eventflow",13,0,13);
if (!h_evtflw) return;
}


void jpsiantisigmaminussigmaplus::book_tree(){
m_tree=new TTree("tree", "jpsiantisigmaminussigmaplus");
if (!m_tree) return;

// common info
m_tree->Branch("run",&m_run,"run/I");
m_tree->Branch("event",&m_event,"event/I");

// charged tracks
m_tree->Branch("ncharged",&m_ncharged,"nchargedTrack/I");
m_tree->Branch("nptrk", &m_nptrk, "nptrk/I");
m_tree->Branch("trkp_p", &m_trkp_p, "trkp_p/D"); 
m_tree->Branch("trkp_px", &m_trkp_px, "trkp_px/D"); 
m_tree->Branch("trkp_py", &m_trkp_py, "trkp_py/D"); 
m_tree->Branch("trkp_pz", &m_trkp_pz, "trkp_pz/D"); 
m_tree->Branch("trkp_theta", &m_trkp_theta, "trkp_theta/D"); 
m_tree->Branch("trkp_phi", &m_trkp_phi, "trkp_phi/D"); 
m_tree->Branch("trkp_eraw", &m_trkp_eraw, "trkp_eraw/D"); 

//vertex
m_tree->Branch("vr0", &m_vr0, "vr0/D");
m_tree->Branch("vz0", &m_vz0, "vz0/D");

//netual tracks
m_tree->Branch("nshow", &m_nshow, "nshow/I");
m_tree->Branch("ngam", &m_ngam, "ngam/I");
m_tree->Branch("raw_gpx", &m_raw_gpx);
m_tree->Branch("raw_gpy", &m_raw_gpy);
m_tree->Branch("raw_gpz", &m_raw_gpz);
m_tree->Branch("raw_ge", &m_raw_ge);
  
m_tree->Branch("raw_phi", &m_raw_phi);
m_tree->Branch("raw_theta", &m_raw_theta);
m_tree->Branch("raw_costheta", &m_raw_costheta);
m_tree->Branch("raw_cstat", &m_raw_cstat);
m_tree->Branch("raw_nhit", &m_raw_nhit);
m_tree->Branch("raw_module", &m_raw_module);
m_tree->Branch("raw_secmom", &m_raw_secmom);
m_tree->Branch("raw_time", &m_raw_time);

// PID info
m_tree->Branch("prob_pip", &m_prob_pip, "prob_pip/D"); 
m_tree->Branch("prob_kp", &m_prob_kp, "prob_kp/D"); 
m_tree->Branch("prob_p", &m_prob_p, "prob_p/D"); 

// save proton info
m_tree->Branch("prp_px", &m_prp_px, "prp_px/D");
m_tree->Branch("prp_py", &m_prp_py, "prp_py/D");
m_tree->Branch("prp_pz", &m_prp_pz, "prp_pz/D");

// save gamma information
m_tree->Branch("m_kmfit_mass",&m_kmfit_mass, "m_kmfit_mass/D");
m_tree->Branch("m_kmfit_energy1",&m_kmfit_energy1, "m_kmfit_energy1/D");
m_tree->Branch("m_kmfit_energy2",&m_kmfit_energy1, "m_kmfit_energy2/D");
}

void jpsiantisigmaminussigmaplus::clearVariables(){
m_run=0;
m_event=0;
m_ncharged=-1;
}

bool jpsiantisigmaminussigmaplus::buildjpsiantisigmaminussigmaplus() {

SmartDataPtr<EvtRecEvent>evtRecEvent(eventSvc(),"/Event/EvtRec/EvtRecEvent");
if(!evtRecEvent) return false;
SmartDataPtr<EvtRecTrackCol> evtRecTrkCol(eventSvc(), "/Event/EvtRec/EvtRecTrackCol");
if(!evtRecTrkCol) return false;

std::vector<int> iPGood, iMGood;
selectChargedTracks(evtRecEvent, evtRecTrkCol, iPGood);
if (selectProton(evtRecTrkCol, iPGood)!=1 ) return false;

std::vector<int> iGam;
selectNeutralTracks(evtRecEvent, evtRecTrkCol, iGam);
if (kinematicFit(evtRecTrkCol, iGam)==0 ); 
if (m_ngam >= 20) return false;
//h_evtflw->Fill(9);

return true;

}


CLHEP::Hep3Vector jpsiantisigmaminussigmaplus::getOrigin() {
  CLHEP::Hep3Vector xorigin(0,0,0);
  IVertexDbSvc*  vtxsvc;
  Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
  if(vtxsvc->isVertexValid()){
    double *dbv = vtxsvc->PrimaryVertex(); 
    xorigin.setX(dbv[0]);
    xorigin.setY(dbv[1]);
    xorigin.setZ(dbv[2]);
  }
  return xorigin; 
}
bool jpsiantisigmaminussigmaplus::passVertexSelection(CLHEP::Hep3Vector xorigin,
				    RecMdcKalTrack* mdcTrk ) {
  HepVector a = mdcTrk->helix();
  HepSymMatrix Ea = mdcTrk->err();
  HepPoint3D point0(0.,0.,0.);
  VFHelix helixip(point0,a,Ea);
  HepPoint3D IP(xorigin[0],xorigin[1],xorigin[2]);
  helixip.pivot(IP);
  HepVector vecipa = helixip.a();
  
  m_vz0 = vecipa[3];
  m_vr0 = vecipa[0];
  
  if(fabs(m_vz0) >= m_vz0cut) return false;
  if(fabs(m_vr0) >= m_vr0cut) return false;
  
  return true;
}

int jpsiantisigmaminussigmaplus::selectChargedTracks(SmartDataPtr<EvtRecEvent> evtRecEvent,
                                 SmartDataPtr<EvtRecTrackCol> evtRecTrkCol,
                                 std::vector<int> & iPGood) {

  CLHEP::Hep3Vector xorigin = getOrigin();

  std::vector<int> iGood;
  iGood.clear();
  iPGood.clear();

 // loop through charged tracks 
 for(int i = 0; i < evtRecEvent->totalCharged(); i++){
   // get mdcTrk 
   EvtRecTrackIterator itTrk=evtRecTrkCol->begin() + i;

   // Good Kalman Track 
   if(!(*itTrk)->isMdcKalTrackValid()) continue;

   if(!(*itTrk)->isMdcTrackValid()) continue;
   RecMdcKalTrack* mdcTrk = (*itTrk)->mdcKalTrack();

   // Good Vertex 
   if (!passVertexSelection(xorigin, mdcTrk) ) continue; 

   // Polar angle cut
   if(fabs(cos(mdcTrk->theta())) > m_cha_costheta_cut) continue;
    iGood.push_back((*itTrk)->trackId());
    
   // otherwise, lepton candidates
    if(mdcTrk->charge()>0) iPGood.push_back((*itTrk)->trackId());
      
 } // end charged tracks

m_ncharged = iGood.size();
m_nptrk = iPGood.size();
if (m_nptrk > 0 ) {
   EvtRecTrackIterator itTrk_p = evtRecTrkCol->begin() + iPGood[0];
   saveTrkInfo(itTrk_p);
  }

return iGood.size();

}

int jpsiantisigmaminussigmaplus::selectProton(SmartDataPtr<EvtRecTrackCol> evtRecTrkCol,
				       std::vector<int> iPGood) {
  int npr = 0;
  bool evtflw_filled = false;
  
//cout<< "I reached here 1 "<< endl;
  for(unsigned int i1 = 0; i1 < iPGood.size(); i1++) {
   EvtRecTrackIterator itTrk_p = evtRecTrkCol->begin() + iPGood[i1];
   RecMdcTrack* mdcTrk_p = (*itTrk_p)->mdcTrack();
  // if (mdcTrk_p->charge() < 0) continue; // only positive charged tracks

     // track PID
      double prob_pip, prob_kp, prob_p; 
      calcTrackPID(itTrk_p, prob_pip, prob_kp, prob_p);  
      
      m_prob_pip = prob_pip;
      m_prob_kp = prob_kp;
      m_prob_p = prob_p;
      if ( !evtflw_filled ) h_evtflw->Fill(4); //PID
 
      // apply vertex fit
      RecMdcKalTrack *prpTrk = (*(evtRecTrkCol->begin()+iPGood[i1]))->mdcKalTrack();
      saveProtonInfo(prpTrk);
          }
      npr++;
      evtflw_filled = true; 
  return npr; 
}

void jpsiantisigmaminussigmaplus::calcTrackPID(EvtRecTrackIterator itTrk_p,
			     double& prob_pip,
			     double& prob_kp,
			     double& prob_p) {
  prob_pip = 999.; 
  prob_kp = 999.; 
  prob_p = 999.; 

  ParticleID * pidp = ParticleID::instance();
  pidp->init();
  pidp->setMethod(pidp->methodProbability());
  pidp->setChiMinCut(4);
  pidp->setRecTrack(*itTrk_p);
  // use PID sub-system
  pidp->usePidSys(pidp->useDedx() | pidp->useTof1() | pidp->useTof2());
  // pidp->usePidSys(pidp->useDedx());
  pidp->identify(pidp->onlyPionKaonProton());
  pidp->calculate();
	if(pidp->IsPidInfoValid()) {


      if((pidp->probProton() > pidp->probPion()) || (pidp->probProton() > pidp->probKaon())) 
    	prob_pip = pidp->probPion();
    	prob_kp  = pidp->probKaon();
    	prob_p   = pidp->probProton();
	}
}

int jpsiantisigmaminussigmaplus::selectNeutralTracks(SmartDataPtr<EvtRecEvent> evtRecEvent,
		                SmartDataPtr<EvtRecTrackCol> evtRecTrkCol,
                    std::vector<int> & iGam) {

  //std::vector<int> iGam;
  iGam.clear();
  std::vector<int> iShow;
  iShow.clear();

  // loop through neutral tracks
  for(int i=evtRecEvent->totalCharged(); i< evtRecEvent->totalTracks(); i++) {
    if (i > m_total_number_of_charged_max) break;

    EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + i ;
    if(!(*itTrk)->isEmcShowerValid()) continue;
    RecEmcShower *emcTrk = (*itTrk)->emcShower();
    iShow.push_back((*itTrk)->trackId());
    
    // TDC window
    if ( !(emcTrk->time() >= m_min_emctime && emcTrk->time() <= m_max_emctime) )
      continue; 

    // Energy threshold
    double abs_costheta(fabs(cos(emcTrk->theta())));
    bool barrel = (abs_costheta < m_costheta_barrel_max); 
    bool endcap = (abs_costheta > m_costheta_endcap_min
		   && abs_costheta < m_costheta_endcap_max);
    double eraw = emcTrk->energy();
    
    if (!m_isZCcondition){     // Cut by "costheta"
      if ( !( (barrel && eraw > m_energy_barrel_min)
	      || (endcap && eraw > m_energy_endcap_min)))  continue; 
    }
    else{                      // Cut by "module"
      int module = emcTrk->module();
      if( module == 1 ){  if( !(eraw > m_energy_barrel_min) ) continue; }
      else{ if( !(eraw > m_energy_endcap_min) ) continue; }
    }

    // photon isolation: the opening angle between a candidate shower
    // and the closest charged track should be larger than 10 degree 
    CLHEP::Hep3Vector emcpos(emcTrk->x(), emcTrk->y(), emcTrk->z());

    // EMC costheta cut 
    double costhe = cos(emcpos.theta());
    if ( fabs(costhe) >= m_gammaCosCut) continue;
    
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
    if (dang < m_photon_iso_angle_min ) continue; 

    iGam.push_back((*itTrk)->trackId());
  } // end loop neutral tracks     

  m_ngam = iGam.size();
  m_nshow = iShow.size();
//cout<<"m_nGam....."  <<  m_ngam <<endl;
  saveGamInfo(iGam, evtRecTrkCol);
  return iGam.size(); 

//cout<<"we are here at the value of m_nGam.....\n"   <<endl;
}

int jpsiantisigmaminussigmaplus::kinematicFit(SmartDataPtr<EvtRecTrackCol> evtRecTrkCol,std::vector<int> iGam)
{

  HepLorentzVector pcms;
  if (!m_isZCcondition)
  {
    pcms = HepLorentzVector(0.011 * m_ecms, 0., 0., m_ecms);
  }
  else
  {
    pcms = HepLorentzVector(0.011 * m_ecms, -0.001, 0.005, m_ecms);
  }

  int nGam = iGam.size();
  KalmanKinematicFit *kmfit = KalmanKinematicFit::instance();
  double chisq_4c = 9999.;
  int ig[2] = {-1, -1};
  HepLorentzVector p4_gamma1, p4_gamma2;

  p4_gamma1 = HepLorentzVector(0, 0, 0, 0);
  p4_gamma2 = HepLorentzVector(0, 0, 0, 0);
  
  int count = 0;
  for (int i1 = 0; i1 < nGam; i1++)
  {
    RecEmcShower *itTrk1 = (*(evtRecTrkCol->begin() + iGam[i1]))->emcShower();
    for (int i2 = 0; i2 < nGam; i2++)
    {
      if (i2 <= i1)
        continue;

        RecEmcShower *itTrk2 = (*(evtRecTrkCol->begin() + iGam[i2]))->emcShower();
        kmfit->init();
        kmfit->AddTrack(0, 0.0, itTrk1);
        kmfit->AddTrack(1, 0.0, itTrk2);
        kmfit->AddFourMomentum(0, pcms);
        //if(!kmfit->Fit(0)) continue;
        //if(!kmfit->Fit(1)) continue;
        bool oksq = kmfit->Fit();
        if (oksq)
       {
         double chisq = kmfit->chisq();

          count++;
          if (chisq < chisq_4c)
          {
           chisq_4c = chisq;
            ig[0] = i1;
            ig[1] = i2;
            p4_gamma1 = kmfit->pfit(0);
            p4_gamma2 = kmfit->pfit(1);
//cout<<"gamma1........."<<p4_gamma1<<endl;
//cout<<"gamma2........."<<p4_gamma2<<endl;
HepLorentzVector p4_gamma12 = p4_gamma1+p4_gamma2;
cout<<"gamma12........."<<p4_gamma12<<endl;
m_kmfit_mass = p4_gamma12.m();
cout<<"invariant mass of gammas........."<<m_kmfit_mass<<endl;
}}}}

//HepLorentzVector p4_gamma12 = p4_gamma1+p4_gamma2;
//cout<<"gamma12........."<<p4_gamma12<<endl;
//m_kmfit_mass = p4_gamma12.m();
//m_kmfit_energy1 = p4_gamma1.e();
//m_kmfit_energy2 = p4_gamma2.e();

//cout<<"energy of gamma1........."<<m_kmfit_energy1<<endl;
//cout<<"energy of gamma2........."<<m_kmfit_energy2<<endl;
//cout<<"invariant mass of gammas........."<<m_kmfit_mass<<endl;
return count;
}

void jpsiantisigmaminussigmaplus::saveTrkInfo(EvtRecTrackIterator itTrk_p) {

  RecMdcTrack* mdcTrk_p = (*itTrk_p)->mdcTrack(); 
  m_trkp_p = mdcTrk_p->p();
  m_trkp_px = mdcTrk_p->px();
  m_trkp_py = mdcTrk_p->py();
  m_trkp_pz = mdcTrk_p->pz();
  m_trkp_theta = mdcTrk_p->theta();
  m_trkp_phi = mdcTrk_p->phi();
  if((*itTrk_p)->isEmcShowerValid()){
    RecEmcShower *emcTrk_p = (*itTrk_p)->emcShower();
    m_trkp_eraw = emcTrk_p->energy();
  }
}

void jpsiantisigmaminussigmaplus::saveGamInfo(std::vector<int> iGam,
			    SmartDataPtr<EvtRecTrackCol> evtRecTrkCol){

// EMC Info
m_raw_gpx->clear();
m_raw_gpy->clear();
m_raw_gpz->clear();
m_raw_ge->clear();

m_raw_phi->clear();
m_raw_theta->clear();
m_raw_costheta->clear();
m_raw_cstat->clear();
m_raw_nhit->clear();
m_raw_module->clear();
m_raw_secmom->clear();
m_raw_time->clear();


for(vector<int>::size_type i=0; i<iGam.size(); i++)  {
    
EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + iGam[i];
RecEmcShower* emcTrk = (*itTrk)->emcShower();
double eraw = emcTrk->energy();
double phi = emcTrk->phi();
double theta = emcTrk->theta();

HepLorentzVector p4 = HepLorentzVector(eraw * sin(theta) * cos(phi),
		eraw * sin(theta) * sin(phi),
		eraw * cos(theta),
		eraw );
    m_raw_gpx->push_back(p4.px());
    m_raw_gpy->push_back(p4.py());
    m_raw_gpz->push_back(p4.pz());
    m_raw_ge->push_back(p4.e());


    int cstat = emcTrk->status();
    int nhit = emcTrk->numHits();
    int module = emcTrk->module();      
    double secmom = emcTrk->secondMoment();      
    double time = emcTrk->time();

    m_raw_phi->push_back(phi);
    m_raw_theta->push_back(theta);
    m_raw_costheta->push_back(cos(theta));
    m_raw_cstat->push_back(cstat);
    m_raw_nhit->push_back(nhit);
    m_raw_module->push_back(module);
    m_raw_secmom->push_back(secmom);
    m_raw_time->push_back(time);
  }

}

void jpsiantisigmaminussigmaplus::saveProtonInfo(RecMdcKalTrack *prpTrk){

  m_prp_px = prpTrk->px();
  m_prp_py = prpTrk->py();
  m_prp_pz = prpTrk->pz();
  
}
