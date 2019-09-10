#include "HyperonDecayAlg/HyperonDecayAlg.h"

HyperonDecayAlg::HyperonDecayAlg(const std::string& name, ISvcLocator* pSvcLocator):Algorithm(name,pSvcLocator){
		declareProperty("Xi0Alg", m_ifXi0Alg = true);
}
HyperonDecayAlg::~HyperonDecayAlg(){
		//add your code for deconstructor
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

StatusCode HyperonDecayAlg::initialize(){
	MsgStream log(msgSvc(), name());
	log<<MSG::INFO<<"HyperonDecayAlg::initialize()"<<endreq;
	//add your code here

	StatusCode sc;
	if(m_ifXi0Alg){
		sc = createSubAlgorithm("Xi0Alg","Xi0Alg",m_Xi0Alg);
		if(sc.isFailure()){
			log<< MSG::ERROR <<" ERROR when creating subAlg. Xi0Alg"<<endreq;
		}   
	}   


	log<< MSG::INFO<<"end of HyperonDecayAlg::initialize()"<<endmsg;
	return StatusCode::SUCCESS;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

StatusCode HyperonDecayAlg::beginRun(){
	MsgStream log(msgSvc(), name());
	log<<MSG::INFO<<"HyperonDecayAlg::beginRun()"<<endreq;
	//add your code here
	return StatusCode::SUCCESS;

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

StatusCode HyperonDecayAlg::execute(){

	StatusCode sc;
	MsgStream log(msgSvc(), name());
	log<<MSG::INFO<<"HyperonDecayAlg::execute()"<<endreq;

	std::vector<Algorithm*>::const_iterator it=subAlgorithms()->begin();
	std::vector<Algorithm*>::const_iterator it_end=subAlgorithms()->end();
	for(;it!=it_end;it++){
		sc = (*it)->execute();
		if(sc.isFailure() ){
			log<<"ERROR when creating subAlg. "<<(*it)->name() << endreq;
		}
	}

	return StatusCode::SUCCESS;

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

StatusCode HyperonDecayAlg::endRun(){
	MsgStream log(msgSvc(), name());
	log<<MSG::INFO<<"HyperonDecayAlg::endRun()"<<endreq;
	//add your code here
	return StatusCode::SUCCESS;

}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

StatusCode HyperonDecayAlg::finalize(){
	MsgStream log(msgSvc(), name());
	std::cout<<"----------------------------------------------------------"<<endl;
	log<<MSG::INFO<<"HyperonDecayAlg::finalize()"<<endreq;
	std::cout<<"HyperonDecayAlg-00-01-00"<<endl;
    std::cout<<"one subAlg for one baryon pair process"<<endl;
	std::cout<<"----------------------------------------------------------"<<endl;
	//add your code here
	return StatusCode::SUCCESS;
}
