#ifndef HyperonDecayAlg_Header
#define HyperonDecayAlg_Header

#include "GaudiKernel/Algorithm.h"
#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/IDataProviderSvc.h"
#include "GaudiKernel/PropertyMgr.h"




using namespace std;

class HyperonDecayAlg:public Algorithm {
  public:
    HyperonDecayAlg(const std::string& name, ISvcLocator* pSvcLocator);
    ~HyperonDecayAlg();
    StatusCode initialize();
    StatusCode beginRun();   
    StatusCode execute();
    StatusCode endRun();
    StatusCode finalize();






  private:
	bool  m_ifXi0Alg;
	Algorithm* m_Xi0Alg;


};


#endif//HyperonDecayAlg_Header
