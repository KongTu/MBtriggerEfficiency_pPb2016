
// system include files
#include <memory>
#include <iostream>
#include <fstream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "DataFormats/HcalDetId/interface/HcalElectronicsId.h"
#include "DataFormats/HcalDigi/interface/HcalQIESample.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"

#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"

#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"


#include "TFile.h"
#include "TH1.h"
#include "TH2F.h"
#include "TProfile2D.h"

//#include <CLHEP/Geometry/Point3D.h>

//add L1 stuff
//#include "CondFormats/L1TObjects/interface/L1GtAlgorithm.h"

#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "L1Trigger/RegionalCaloTrigger/interface/L1RCTProducer.h"
#include "DataFormats/L1TCalorimeter/interface/CaloTower.h"
#include "DataFormats/L1Trigger/interface/EGamma.h"
#include "DataFormats/L1Trigger/interface/Muon.h"
#include "DataFormats/L1Trigger/interface/Jet.h"
#include "DataFormats/L1Trigger/interface/Tau.h"
#include "DataFormats/L1Trigger/interface/EtSum.h"

#include "DataFormats/L1TGlobal/interface/GlobalAlgBlk.h"
#include "DataFormats/L1TGlobal/interface/GlobalExtBlk.h"
#include "DataFormats/L1Trigger/interface/BXVector.h"

#include "DataFormats/L1GlobalTrigger/interface/L1GtObject.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GtFdlWord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GtLogicParser.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GtObject.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GtTechnicalTrigger.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GtTechnicalTriggerRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GtTriggerMenuLite.h"

// class declaration
//

class MBtriggerEfficiency_Stage2 : public edm::EDAnalyzer {
public:
  explicit MBtriggerEfficiency_Stage2(const edm::ParameterSet&);
  ~MBtriggerEfficiency_Stage2();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  
  virtual void beginJob();
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob();
  
  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
  //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
  //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
  
  // ----------member data ---------------------------

  TH1D* ZB_vsLumi;
  TH1D* bxNum;

  edm::InputTag m_l1stage2globalAlgBlk;

  edm::EDGetTokenT<GlobalAlgBlkBxCollection> l1tStage2uGtSource_;

  bool useReco;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
MBtriggerEfficiency_Stage2::MBtriggerEfficiency_Stage2(const edm::ParameterSet& iConfig)
{

  m_l1stage2globalAlgBlk = edm::InputTag("hltGtStage2Digis");

  l1tStage2uGtSource_ = consumes<GlobalAlgBlkBxCollection>( m_l1stage2globalAlgBlk );

  useReco=iConfig.getParameter<bool>("useReco");


}
MBtriggerEfficiency_Stage2::~MBtriggerEfficiency_Stage2()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void MBtriggerEfficiency_Stage2::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;

  cout << "test" << endl;

  //select particular lumi, bunch, etc...
  int lsec=iEvent.eventAuxiliary().luminosityBlock();
  int bx=iEvent.eventAuxiliary().bunchCrossing();

  // //if( lsec > 270 ) std::cout<<"lsec: "<<lsec<<"   // bx number: "<<bx<<std::endl;

  bxNum->Fill( bx );
  ZB_vsLumi->Fill( lsec );

  // if (!useReco){

  edm::Handle<GlobalAlgBlkBxCollection> uGtAlgs;
  iEvent.getByToken(l1tStage2uGtSource_, uGtAlgs);

  cout << "test1: " << uGtAlgs->getFirstBX() << endl;
  cout << "test2: " << uGtAlgs->getLastBX() << endl;

    // for (int ibx=uGtAlgs->getFirstBX(); ibx <= uGtAlgs->getLastBX(); ++ibx) {

    //   cout << "test" << endl;

    //   for (auto itr = uGtAlgs->begin(ibx); itr != uGtAlgs->end(ibx); ++itr) {
        
    //     for(int algoBit = 0; algoBit < 512; ++algoBit) {
                
    //              // Algorithm bits after BX mask, before prescale 
    //              if(itr->getAlgoDecisionInitial(algoBit)) {
    //                     std::cout << "test" << std::endl;
    //              }
    //     }
    //   }
    // }

    // edm::Handle<HFDigiCollection> digi;
    // iEvent.getByToken(hfDigiTag,digi);
  
    // HFDigiCollection::const_iterator i;
    
  //}
}
// ------------ method called once each job just before starting event loop  ------------
void 
MBtriggerEfficiency_Stage2::beginJob()
{

  edm::Service<TFileService> fs;
  TH1D::SetDefaultSumw2();

  bxNum = fs->make<TH1D>("bxNum",";bxNum",5000,0,5000);
  ZB_vsLumi = fs->make<TH1D>("ZB_vsLumi",";ZB_vsLumi",1000,0,1000);

}

// ------------ method called once each job just after ending the event loop  ------------
void 
MBtriggerEfficiency_Stage2::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------

void 
MBtriggerEfficiency_Stage2::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
/*
  bool useL1EventSetup = true;
  bool useL1GtTriggerMenuLite = false;
  
  // could be added in beginRun(...) - if not added, the caching will be done in analyze/produce/filter method
  m_l1GtUtils.getL1GtRunCache(iRun, iSetup, useL1EventSetup, useL1GtTriggerMenuLite);
*/
}

// ------------ method called when ending the processing of a run  ------------
/*
void 
MBtriggerEfficiency_Stage2::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
MBtriggerEfficiency_Stage2::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
MBtriggerEfficiency_Stage2::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
MBtriggerEfficiency_Stage2::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MBtriggerEfficiency_Stage2);
