// -*- C++ -*- //
//
// Description: J/psi   ->  antisigmaminus  sigmaplus
//
// Original Author:  Amit pathak <amitraahul@itp.ac.cn>
//         Created:  [2018-05-17 Fri 14:30] 
//         Inspired by SHI Xin's code 
//         Helped by maoqiang
//


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
// class declaration //
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
double m_total_number_of_charged_max;

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
//Neutral Tracks
//
int m_ncharged;

//
//jpsiantisigmaminussigmaplus
//
int m_ntrk;


//
//functions
//
void book_histogram();
void book_tree();
void clearVariables();
bool buildjpsiantisigmaminussigmaplus();

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
declareProperty("TotalNumberOfChargedMax",m_total_number_of_charged_max = 50);

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

}

void jpsiantisigmaminussigmaplus::clearVariables(){
m_run=0;
m_event=0;
}
bool jpsiantisigmaminussigmaplus::buildjpsiantisigmaminussigmaplus() {

SmartDataPtr<EvtRecEvent>evtRecEvent(eventSvc(),"/Event/EvtRec/EvtRecEvent");
	if(!evtRecEvent) return false;

	h_evtflw->Fill(9);

	m_ncharged = evtRecEvent->totalCharged();
	if (m_ncharged != 0) return false;
	h_evtflw->Fill(1); // N_{Good} = 0

	std::vector<int> iGam;
	iGam.clear();
	std::vector<int> iShow;
	iShow.clear();


return true;


}