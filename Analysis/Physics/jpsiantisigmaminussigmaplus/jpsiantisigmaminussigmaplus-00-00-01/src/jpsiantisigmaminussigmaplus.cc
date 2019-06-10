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

//output file
std::string m_output_filename;
  bool m_isMonteCarlo; 
  bool m_eventrate;
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

//
//jpsiantisigmaminussigmaplus
//
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
m_tree(0)
{
declareProperty("OutputFileName",m_output_filename);
declareProperty("IsMonteCarlo",m_isMonteCarlo);
declareProperty("Ecms", m_ecms = 3.686);
declareProperty("Vr0cut", m_vr0cut=1.0);
declareProperty("Vz0cut", m_vz0cut=10.0);
declareProperty("ChaCosthetaCut", m_cha_costheta_cut=0.93);
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
//selectNeutralTracks(evtRecEvent, evtRecTrkCol);

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
