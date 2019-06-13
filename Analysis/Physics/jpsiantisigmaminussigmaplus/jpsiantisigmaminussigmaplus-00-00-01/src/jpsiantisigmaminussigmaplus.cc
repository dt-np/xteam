// -*- C++ -*- //
//
// Description: J/psi   ->  antisigmaminus  sigmaplus
//
// Original Author:  Amit pathak <amitraahul@itp.ac.cn>
//         Created:  [2019-05-17 Fri 14:30] 
//         Inspired by SHI Xin's code 
//         

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

//
//functions
//
void book_histogram();
void book_tree();
void clearVariables();
bool buildjpsiantisigmaminussigmaplus();
int selectChargedTracks(SmartDataPtr<EvtRecEvent>,
	  SmartDataPtr<EvtRecTrackCol>,
	  std::vector<int> &,
    std::vector<int> &);
int selectNeutralTracks(SmartDataPtr<EvtRecEvent>,
		SmartDataPtr<EvtRecTrackCol>);
void saveGamInfo(std::vector<int>,
		SmartDataPtr<EvtRecTrackCol>);
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
declareProperty("Ecms", m_ecms = 3.686);
declareProperty("Vr0cut", m_vr0cut=1.0);
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
m_tree->Branch("ncharged",&m_ncharged,"nchargedTrack/I");
m_tree->Branch("nptrk", &m_nptrk, "nptrk/I");
m_tree->Branch("nmtrk", &m_nmtrk, "nmtrk/I");

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
selectChargedTracks(evtRecEvent, evtRecTrkCol, iPGood, iMGood);

//if(selectLeptonPlusLeptonMinus(evtRecTrkCol, iPGood, iMGood) != 1) return false; 
selectNeutralTracks(evtRecEvent, evtRecTrkCol);
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
                                 std::vector<int> & iPGood,
                                 std::vector<int> & iMGood) {

  CLHEP::Hep3Vector xorigin = getOrigin();

  std::vector<int> iGood;
  iGood.clear();
  iPGood.clear();
  iMGood.clear();

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
    if(mdcTrk->charge()<0) iMGood.push_back((*itTrk)->trackId());
    
 } // end charged tracks

m_ncharged = iGood.size();
m_nptrk = iPGood.size();
m_nmtrk = iMGood.size();

  return iGood.size();

}

int jpsiantisigmaminussigmaplus::selectNeutralTracks(SmartDataPtr<EvtRecEvent> evtRecEvent,
				   SmartDataPtr<EvtRecTrackCol> evtRecTrkCol) {

  std::vector<int> iGam;
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

  //saveGamInfo(iGam, evtRecTrkCol);
  
  return iGam.size(); 
}


void jpsiantisigmaminussigmaplus::saveGamInfo(std::vector<int> iGam,
			    SmartDataPtr<EvtRecTrackCol> evtRecTrkCol){

std::cout<<"This function may have a problem......"<<std::endl;

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

    cout<< "eraw: "<<eraw<<endl;
    cout<< "Phi: "<<phi<<endl;
    cout<<" Theta: : "<<theta<<endl;
    cout<<"Checking the error"<< endl;

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
