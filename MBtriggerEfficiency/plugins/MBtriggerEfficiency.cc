
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

#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TProfile2D.h"

//#include <CLHEP/Geometry/Point3D.h>

//add L1 stuff
#include "CondFormats/L1TObjects/interface/L1GtAlgorithm.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMaps.h"
 
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMap.h"

#include "DataFormats/L1GlobalTrigger/interface/L1GtTriggerMenuLite.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenuFwd.h"

#include "L1Trigger/GlobalTriggerAnalyzer/interface/L1GtUtils.h"

#include "DataFormats/L1Trigger/interface/L1JetParticle.h"
#include "DataFormats/L1Trigger/interface/L1JetParticleFwd.h"

#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
#include "DataFormats/CaloTowers/interface/CaloTower.h"

// class declaration
//

class MBtriggerEfficiency : public edm::EDAnalyzer {
public:
  explicit MBtriggerEfficiency(const edm::ParameterSet&);
  ~MBtriggerEfficiency();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  TFile* outputFile;
  TH1F* allChanSignalLong;
  TH1F* allChanSignalShort;
  TH1F* allChanSignal;
  TH1F* sigPerChanLong[26][36];
  TH1F* sigPerChanShort[26][36];
  TH1F* amplVSsampl;
  
  TH1F* sig[2][26][36];
  
  TProfile2D* sigAboveThr1;
  TProfile2D* sigAboveThrShort1;
  TProfile2D* sigProfile;
  TProfile2D* sigProfileShort;
  
  TH1F* accPerEvt;
  TH1F* accPerEvtPlus;
  TH1F* accPerEvtMinus;
  TH1F* accPerEvt2sliceFront;
  TH1F* accPerEvt2sliceBack;

  TH2F* allChanEtaPhi;
  TH1F* nChanLong;
  TH1F* nChanShort;
  
  TH2F* chanAboveThrFileLong;
  TH2F* chanAboveThrFileShort;
  TH1F* accPerEvtThrFile;
  
  TH1F* idFired;
  TH1F* idFired_frac;
  TH1F* nMBHF1_firedBX;
  TH1F* nMBHF2_firedBX;

  TH1F* crossTest_HF1;
  TH1F* crossTest_HF2;

  TH1F* jetCrossTest8;
  TH1F* jetCrossTest12;

  TH1F* bxNum;
  
  int evtsTot;

  TH1F* HF1_OR_vsLumi;
  TH1F* HF2_OR_vsLumi;
  
  TH1F* ZB_vsLumi;

  TH1F* hL1jetsEta8;
  TH1F* hL1jetsEta12;
  
  double thresholdsLong[26][36];
  double thresholdsShort[26][36];
  
  uint32_t totalTime;
  
  std::vector<std::string> trgList;
  // string trgList[]={'L1_MinimumBiasHF1_OR','L1_MinimumBiasHF2_OR','L1_MinimumBiasHF1_AND','L1_MinimumBiasHF2_AND','L1_SingleJet8_BptxAND','L1_SingleJet12_BptxAND',"L1_SingleJet16','L1_SingleJet20','L1_DoubleJet20'};

  std::string outfname;
  edm::InputTag gtDigiTag;
  edm::InputTag gctDigiTag;
  edm::InputTag l1GtRecordInputTag;
  edm::InputTag l1GtReadoutRecordInputTag;
  edm::InputTag l1GtTriggerMenuLiteInputTag;
  edm::EDGetTokenT<HFDigiCollection> hfDigiTag;
  edm::EDGetTokenT<CaloTowerCollection> caloTowerTag;
  edm::EDGetTokenT<HFRecHitCollection> hfRechitTag;
  edm::EDGetTokenT<reco::CaloJetCollection> caloJetTag;

  edm::EDGetTokenT<l1extra::L1JetParticleCollection>  m_l1CenJetToken;
  edm::EDGetTokenT<l1extra::L1JetParticleCollection>  m_l1ForJetToken;
  edm::EDGetTokenT<l1extra::L1JetParticleCollection>  m_l1TauJetToken;

  bool useReco;
  bool useMC;
  const CaloGeometry* geo;
  
  TH1F* hCaloTowerET[8];
  TH1F* hCaloTowerETtrig8[8];
  TH1F* hCaloTowerETtrig12[8];
  TH1F* hCaloTowerETtrigMB[8];

  TH1F* hRecHitET[8];
  TH1F* hRecHitETtrig8[8];
  TH1F* hRecHitETtrig12[8];
  TH1F* hRecHitETtrigMB[8];

  TH1F* hCaloJetPlusET;
  TH1F* hCaloJetPlusETtrig8;
  TH1F* hCaloJetPlusETtrig12;
  TH1F* hCaloJetPlusETtrigMB;

  TH1F* hCaloJetMinusET;
  TH1F* hCaloJetMinusETtrig8;
  TH1F* hCaloJetMinusETtrig12;
  TH1F* hCaloJetMinusETtrigMB;

private:
  L1GtUtils m_l1GtUtils;
  
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  
  virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
  //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
  //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
  //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
  
  // ----------member data ---------------------------
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
MBtriggerEfficiency::MBtriggerEfficiency(const edm::ParameterSet& iConfig):
  m_l1GtUtils(iConfig, consumesCollector(), true)//this is important for 80x to compile
{
  l1GtRecordInputTag = iConfig.getParameter<edm::InputTag>("l1GtRecordInputTag");
  l1GtReadoutRecordInputTag = iConfig.getParameter<edm::InputTag>("l1GtReadoutRecordInputTag");
  l1GtTriggerMenuLiteInputTag = iConfig.getParameter<edm::InputTag>("l1GtTriggerMenuLiteInputTag");
  outfname=iConfig.getParameter<std::string>("outputFileName");
  gtDigiTag=iConfig.getParameter<edm::InputTag>("gtDigiTag");
  gctDigiTag=iConfig.getParameter<edm::InputTag>("gctDigiTag");
  caloTowerTag=consumes<CaloTowerCollection>(iConfig.getParameter<edm::InputTag>("caloTowerTag"));
  hfRechitTag = consumes<HFRecHitCollection>(iConfig.getParameter<edm::InputTag>("hfRechitTag"));
  caloJetTag = consumes<reco::CaloJetCollection>(iConfig.getParameter<edm::InputTag>("caloJetTag"));
  hfDigiTag = consumes<HFDigiCollection>(iConfig.getParameter<edm::InputTag>("hfDigiTag"));
  m_l1CenJetToken = consumes<l1extra::L1JetParticleCollection>(iConfig.getParameter<edm::InputTag>("m_l1CenJetToken"));
  m_l1ForJetToken = consumes<l1extra::L1JetParticleCollection>(iConfig.getParameter<edm::InputTag>("m_l1ForJetToken"));
  m_l1TauJetToken = consumes<l1extra::L1JetParticleCollection>(iConfig.getParameter<edm::InputTag>("m_l1TauJetToken"));
  useReco=iConfig.getParameter<bool>("useReco");
  useMC=iConfig.getParameter<bool>("useMC");
  //   tok_ho_  = consumes<HORecHitCollection>(iConfig.getParameter<edm::InputTag>("HOInput"));

  trgList.push_back("L1Tech_BPTX_plus_AND_NOT_minus.v0");
  trgList.push_back("L1Tech_BPTX_minus_AND_not_plus.v0");
  trgList.push_back("L1Tech_BPTX_quiet.v0");
  trgList.push_back("L1_ZeroBias");
  trgList.push_back("L1_MinimumBiasHF1_OR");
  trgList.push_back("L1_MinimumBiasHF2_OR");
  trgList.push_back("L1_MinimumBiasHF1_AND");
  trgList.push_back("L1_MinimumBiasHF2_AND");
  //  trgList.push_back("L1_SingleJet8_BptxAND");
  //  trgList.push_back("L1_SingleJet12_BptxAND");
  trgList.push_back("L1_SingleJet36");
  trgList.push_back("L1_SingleJet52");
  trgList.push_back("L1_SingleJet16");
  trgList.push_back("L1_DoubleJet20");
  
  outputFile=new TFile(outfname.c_str(),"RECREATE");
  allChanSignalLong=new TH1F("allChanSignalLong","allChanSignalLong",1000,0,1000);
  allChanSignalShort=new TH1F("allChanSignalShort","allChanSignalShort",1000,0,1000);
  allChanSignal=new TH1F("allChanSignal","allChanSignal",1000,0,1000);
  allChanEtaPhi=new TH2F("allChanEtaPhi","allChanEtaPhi",100,-50,50,73,0,73);
  nChanLong=new TH1F("nChanLong","nChanLong",10000,0,10000);
  nChanShort=new TH1F("nChanShort","nChanShort",10000,0,10000);
  sigAboveThr1=new TProfile2D("sigAboveThr1","sigAboveThr1",100,-50,50,73,0,73,0,10000);
  sigAboveThrShort1=new TProfile2D("sigAboveThrShort1","sigAboveThrShort1",100,-50,50,73,0,73,0,10000);
  sigProfile=new TProfile2D("sigProfile","sigProfile",100,-50,50,73,0,73,0,10000);
  sigProfileShort=new TProfile2D("sigProfileShort","sigProfileShort",100,-50,50,73,0,73,0,10000);
  
  chanAboveThrFileLong=new TH2F("chanAboveThrFileLong","chanAboveThrFileLong",100,-50,50,73,0,73);
  chanAboveThrFileShort=new TH2F("chanAboveThrFileShort","chanAboveThrFileShort",100,-50,50,73,0,73);
  accPerEvtThrFile=new TH1F("accPerEvtThrFile","accPerEvtThrFile",2,1,3); 
  
  bxNum=new TH1F("bxNum","bxNum",5000,0,5000);
  
  idFired=new TH1F("idFired","idFired",13,0,13);
  idFired_frac=new TH1F("idFired_frac","idFired_frac",13,0,13);

  nMBHF1_firedBX=new TH1F("nMBHF1_firedBX","nMBHF1_firedBX",10000,0,10000);
  nMBHF2_firedBX=new TH1F("nMBHF2_firedBX","nMBHF2_firedBX",10000,0,10000);

  HF1_OR_vsLumi=new TH1F("HF1_OR_vsLumi","HF1_OR_vsLumi",1000,0,1000);
  HF2_OR_vsLumi=new TH1F("HF2_OR_vsLumi","HF2_OR_vsLumi",1000,0,1000);
  
  ZB_vsLumi=new TH1F("ZB_vsLumi","ZB_vsLumi",1000,0,1000);

  crossTest_HF1=new TH1F("crossTestHF1","crossTestHF1",3,0,3);
  crossTest_HF2=new TH1F("crossTestHF2","crossTestHF2",3,0,3);

  jetCrossTest8=new TH1F("jetCrossTest8","jetCrossTest8",3,0,3);
  jetCrossTest12=new TH1F("jetCrossTest12","jetCrossTest12",3,0,3);

  hL1jetsEta8=new TH1F("hL1jetsEta8","hL1jetsEta8",110,-5.5,5.5);
  hL1jetsEta12=new TH1F("hL1jetsEta12","hL1jetsEta12",110,-5.5,5.5);

  char tmp[100];

  for (int i=0; i<8; i++)
    {
      sprintf(tmp,"hCaloTowerET_%d",i);
      hCaloTowerET[i]=new TH1F(tmp,tmp,1000,0,1000);
      sprintf(tmp,"hCaloTowerETtrig8_%d",i);
      hCaloTowerETtrig8[i]=new TH1F(tmp,tmp,1000,0,1000);
      sprintf(tmp,"hCaloTowerETtrig12_%d",i);
      hCaloTowerETtrig12[i]=new TH1F(tmp,tmp,1000,0,1000);
      sprintf(tmp,"hCaloTowerETtrigMB_%d",i);
      hCaloTowerETtrigMB[i]=new TH1F(tmp,tmp,1000,0,1000);

      sprintf(tmp,"hRecHitET_%d",i);
      hRecHitET[i]=new TH1F(tmp,tmp,1000,0,1000);
      sprintf(tmp,"hRecHitETtrig8_%d",i);
      hRecHitETtrig8[i]=new TH1F(tmp,tmp,1000,0,1000);
      sprintf(tmp,"hRecHitETtrig12_%d",i);
      hRecHitETtrig12[i]=new TH1F(tmp,tmp,1000,0,1000);
      sprintf(tmp,"hRecHitETtrigMB_%d",i);
      hRecHitETtrigMB[i]=new TH1F(tmp,tmp,1000,0,1000);
    }

  hCaloJetPlusET=new TH1F("hCaloJetPlusET","hCaloJetPlusET",1000,0,1000);
  hCaloJetPlusETtrig8=new TH1F("hCaloJetPlusETtrig8","hCaloJetPlusETtrig8",1000,0,1000);
  hCaloJetPlusETtrig12=new TH1F("hCaloJetPlusETtrig12","hCaloJetPlusETtrig12",1000,0,1000);
  hCaloJetPlusETtrigMB=new TH1F("hCaloJetPlusETtrigMB","hCaloJetPlusETtrigMB",1000,0,1000);

  hCaloJetMinusET=new TH1F("hCaloJetMinusET","hCaloJetMinusET",1000,0,1000);
  hCaloJetMinusETtrig8=new TH1F("hCaloJetMinusETtrig8","hCaloJetMinusETtrig8",1000,0,1000);
  hCaloJetMinusETtrig12=new TH1F("hCaloJetMinusETtrig12","hCaloJetMinusETtrig12",1000,0,1000);
  hCaloJetMinusETtrigMB=new TH1F("hCaloJetMinusETtrigMB","hCaloJetMinusETtrigMB",1000,0,1000);

  std::ifstream thrFileShort;
  thrFileShort.open("thresholdsShort_cosmic.txt");
  
  std::ifstream thrFileLong;
  thrFileLong.open("thresholdsLong_cosmic.txt");
  
  for (int l=0; l<26; l++)
    {
      for (int k=0; k<36; k++)
  {
    thrFileLong>>thresholdsLong[l][k];
    thrFileShort>>thresholdsShort[l][k];
    

    sprintf(tmp,"sigLong_%d_%d",l,k);
    sigPerChanLong[l][k]=new TH1F(tmp,tmp,1000,0,1000);
    sprintf(tmp,"sigShort_%d_%d",l,k);
    sigPerChanShort[l][k]=new TH1F(tmp,tmp,1000,0,1000);
    int eta, phi;
    if (l<13) eta=-29-l;
    else eta=16+l;
    phi=(k+1)*2-1;
    for (int p=0; p<2; p++)
      {
        sprintf(tmp,"sig_%d_%d_%d",p,eta,phi);
        sig[p][l][k]=new TH1F(tmp,tmp,1000,0,1000); 
      }
  }
      thrFileLong.getline(tmp,100,'\n');
      thrFileShort.getline(tmp,100,'\n');
    }
  
  amplVSsampl=new TH1F("amplVSsampl","amplVSsampl",10,0,10);
  
  accPerEvt=new TH1F("accPerEvt","accPerEvt",40,0,40);
  accPerEvt->TH1F::Sumw2();
  accPerEvtPlus=new TH1F("accPerEvtPlus","accPerEvtPlus",40,0,40);
  accPerEvtPlus->TH1F::Sumw2();
  accPerEvtMinus=new TH1F("accPerEvtMinus","accPerEvtMinus",40,0,40);
  accPerEvtMinus->TH1F::Sumw2();
  accPerEvt2sliceFront=new TH1F("accPerEvt2sliceFront","accPerEvt2sliceFront",40,0,40);
  accPerEvt2sliceFront->TH1F::Sumw2();
  accPerEvt2sliceBack=new TH1F("accPerEvt2sliceBack","accPerEvt2sliceBack",40,0,40);
  accPerEvt2sliceBack->TH1F::Sumw2();
  
  evtsTot=0;
  //now do what ever initialization is needed
  
  totalTime=0;

}


MBtriggerEfficiency::~MBtriggerEfficiency()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void MBtriggerEfficiency::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  //select particular lumi, bunch, etc...
  int lsec=iEvent.eventAuxiliary().luminosityBlock();
  int bx=iEvent.eventAuxiliary().bunchCrossing();

  //if( lsec > 270 ) std::cout<<"lsec: "<<lsec<<"   // bx number: "<<bx<<std::endl;

  bxNum->Fill(bx,1);
  
  ZB_vsLumi->Fill(lsec,1);

  //if ( lsec<270 || lsec > 464 ) return;

  evtsTot++;
  
  bool fire[40];
  bool fireFront[40];
  bool fireBack[40];
  bool firePlus[40];
  bool fireMinus[40];
  bool fireShortThr1=false;
  bool fireLongThr1=false;
  bool fireShortThr2=false;
  bool fireLongThr2=false;

  if (!useReco){
    
    edm::Handle<HFDigiCollection> digi;
    iEvent.getByToken(hfDigiTag,digi);
  
    HFDigiCollection::const_iterator i;
    
    for (int k=0; k<40; k++){
      fire[k]=false;
      fireFront[k]=false;
      fireBack[k]=false;
      firePlus[k]=false;
      fireMinus[k]=false;
    }
      
    int nChLong=0;
    int nChShort=0;
      
    for (i=digi->begin(); i!=digi->end(); i++) {
      
      HcalDetId cell = i->id();
      int idepth=cell.depth();
      int ieta=cell.ieta();
      int iphi=cell.iphi();
      //  if (abs(ieta)>36) continue;
      if (idepth==1) 
        {
          nChLong++;
          allChanEtaPhi->Fill(ieta,iphi,1);
        }
      if (idepth==2) nChShort++;
      
      int ampl=0;
      int amplFront=0;
      int amplBack=0;
      int digiSize=i->size();

      if( digiSize > 4 ) std::cout << "digiSize: " << digiSize << std::endl;
      
      
      for (int k=0; k<digiSize; k++){
        HcalQIESample dSample=i->sample(k);
        //int capid=dSample.capid();
        int adc=dSample.adc();
        int etaind, phiind;
        if (ieta<0) etaind=abs(ieta)-29;
        else etaind=ieta-16;
        phiind=(iphi-1)/2;
        sig[idepth-1][etaind][phiind]->Fill(adc,1);
        amplVSsampl->Fill(k,adc);

        if (k==2) ampl+=adc;
        if (k==1) amplFront+=adc;
        if (k==3) amplBack+=adc;
      }    
      if (idepth==1){
        allChanSignalLong->Fill(ampl,1);
        sigPerChanLong[abs(ieta/1000)][iphi]->Fill(ampl,1);
        if (ampl>11) sigAboveThr1->Fill(ieta,iphi,ampl,1);
        sigProfile->Fill(ieta,iphi,ampl,1);
        for (int p=0; p<40; p++){
          if (ampl>p) fire[p]=true;
          if (ampl>p&&ieta>0) firePlus[p]=true;
          if (ampl>p&&ieta<0) fireMinus[p]=true;
          if (amplFront+ampl>p) fireFront[p]=true;
          if (amplBack+ampl>p) fireBack[p]=true;
        }
        if (ampl>11){
          //thresholdsLong[etaind][phiind])
          chanAboveThrFileLong->Fill(ieta,iphi,1);
          fireLongThr1=true;
        }
        if (ampl>17){
          fireLongThr2=true;
        }
      }
      if (idepth==2){
        allChanSignalShort->Fill(ampl,1);
        sigPerChanShort[abs(ieta/1000)][iphi]->Fill(ampl,1);
        if (ampl>11) sigAboveThrShort1->Fill(ieta,iphi,ampl,1);
        sigProfileShort->Fill(ieta,iphi,ampl,1);
        for (int p=0; p<40; p++){
          if (ampl>p) fire[p]=true;
          if (ampl>p&&ieta>0) firePlus[p]=true;
          if (ampl>p&&ieta<0) fireMinus[p]=true;
          if (amplFront>p||ampl>p) fireFront[p]=true;
          if (amplBack>p||ampl>p) fireBack[p]=true;
        }
        if (ampl>11){
          //adc>thresholdsShort[etaind][phiind])
            
          chanAboveThrFileShort->Fill(ieta,iphi,1);
          fireShortThr1=true;                        
        }
        if (ampl>17){
          fireShortThr2=true;
        }
      }
    }
    for (int k=0; k<40; k++){
      if (fire[k]) accPerEvt->Fill(k,1);
      if (fireFront[k]) accPerEvt2sliceFront->Fill(k,1);
      if (fireBack[k]) accPerEvt2sliceBack->Fill(k,1);
      if (firePlus[k]) accPerEvtPlus->Fill(k,1);
      if (fireMinus[k]) accPerEvtMinus->Fill(k,1);
    }

    if (fireLongThr1||fireShortThr1){
      accPerEvtThrFile->Fill(1,1);
    }
      // if (fireLongThr2||fireShortThr2) 
      //  {
      
      //       accPerEvtThrFile->Fill(1,1);
      //  }
      
    nChanLong->Fill(nChLong,1);
    nChanShort->Fill(nChShort,1);
      //std::cout<<nChLong<<std::endl;
    
    }//end of !useReco
   

   ////////////////////////////////////////
      
/*   
   edm::ESHandle<L1GtTriggerMenu> menuRcd;
   iSetup.get<L1GtTriggerMenuRcd>().get(menuRcd) ;
   const L1GtTriggerMenu* menu = menuRcd.product();
   
      
  for (CItAlgo algo = menu->gtAlgorithmMap().begin(); algo!=menu->gtAlgorithmMap().end(); ++algo) {
    std::cout << "Name: " << (algo->second).algoName() << " Alias: " << (algo->second).algoAlias() << std::endl;
  }
*/
     
   bool useL1EventSetup = true;
   bool useL1GtTriggerMenuLite = false;
   
   // could be added in beginRun(...) - if not added, the caching will be done in analyze/produce/filter method
//   m_l1GtUtils.getL1GtRunCache(iRun, iSetup, useL1EventSetup, useL1GtTriggerMenuLite);
   
   // must be added in analyze/produce/filter method
   m_l1GtUtils.getL1GtRunCache(iEvent, iSetup, useL1EventSetup, useL1GtTriggerMenuLite);
   
  //retreive L1 event setup:
  // m_l1GtUtils.retrieveL1EventSetup(iSetup);

  // edm::InputTag* l1GTRt=new edm::InputTag("foo");

  // m_l1GtUtils.getL1GtRecordInputTag(iEvent, *l1GTRt, *l1GTRRt);

  // std::cout<<"tags:   "<<l1GTRt->instance()<<"_"<<l1GTRt->label()<<"     "<<l1GTRRt->instance()<<"_"<<l1GTRRt->label()<<std::endl;

  //check if ZeroBias has fired
  int iErrorCode=-1;
  bool ZBfired=m_l1GtUtils.decisionBeforeMask(iEvent, "L1_SingleJet16", iErrorCode);
  std::cout << "L1_SingleJet16: " << ZBfired << std::endl;
  std::cout << "errorcode: " << iErrorCode << std::endl;

  //loop through other trigs
  //std::cout<<"go?  "<<trgList.size()<<std::endl;
   
  bool fireHF1=false;
  bool fireHF2=false;

  bool fireJet8_fromGT=false;
  bool fireJet12_fromGT=false;   

  iErrorCode=-1;
  for (uint32_t iTr=0; iTr < trgList.size(); iTr++){
     
     iErrorCode = -1;      
     bool decisionBeforeMaskAlgTechTrig = m_l1GtUtils.decisionBeforeMask(iEvent, trgList[iTr], iErrorCode);
     
     if (iErrorCode == 0){
       std::cout<<"code0"<<std::endl;
       if (decisionBeforeMaskAlgTechTrig){
          if (iTr==4){
             std::cout << "code4" << std::endl;
             nMBHF1_firedBX->Fill(bx,1);
             HF1_OR_vsLumi->Fill(lsec,1);
             fireHF1=true;
          }
         if (iTr==5){
             nMBHF2_firedBX->Fill(bx,1);
             HF2_OR_vsLumi->Fill(lsec,1);
             fireHF2=true;
          }
          if (iTr==8) fireJet8_fromGT=true;
          if (iTr==9) fireJet12_fromGT=true;
          //        std::cout<<"yes"<<std::endl;
         idFired->Fill(iTr+1,1);
        }
         //trgFirediredBptxGate[iTr]++;
         //   if (decisionBeforeMaskAlgTechTrig) trgFired[iTr]++;
      } 
      else if (iErrorCode == 210001){
        std::cout<<trgList[iTr]<<" does not exist in the L1 menu"<<std::endl; //algorithm / technical trigger  does not exist in the L1 menu
      }  
      else{
        std::cout<<"err:  "<<iErrorCode<<std::endl;// error - see error code, do whatever needed 
         
      }
      
      std::cout<<"MENU USED: "<<m_l1GtUtils.l1TriggerMenu()<<std::endl;

  }

  if ((fireLongThr1||fireShortThr1)&&fireHF2) crossTest_HF1->Fill(0.1,1);
  if ((fireLongThr1||fireShortThr1)&&(!fireHF2)) crossTest_HF1->Fill(1.1,1);
  if ((!(fireLongThr1||fireShortThr1))&&fireHF2) crossTest_HF1->Fill(2.1,1);

  if ((fireLongThr2||fireShortThr2)&&fireHF1) crossTest_HF2->Fill(0.1,1);
  if ((fireLongThr2||fireShortThr2)&&(!fireHF1)) crossTest_HF2->Fill(1.1,1);
  if ((!(fireLongThr2||fireShortThr2))&&fireHF1) crossTest_HF2->Fill(2.1,1);

  /////////////////////////////////////////////

  //now check L1ExtraParticles

  bool fireJet8=false;
  bool fireJet12=false;

  edm::Handle<l1extra::L1JetParticleCollection> l1cjets;
  iEvent.getByToken(m_l1CenJetToken,l1cjets);

  edm::Handle<l1extra::L1JetParticleCollection> l1fjets;
  iEvent.getByToken(m_l1ForJetToken,l1fjets);

  edm::Handle<l1extra::L1JetParticleCollection> l1tjets;
  iEvent.getByToken(m_l1TauJetToken,l1tjets);

  for (l1extra::L1JetParticleCollection::const_iterator tj=l1cjets->begin(); tj!=l1cjets->end(); tj++){
    if (tj->pt()>36){
      hL1jetsEta8->Fill(tj->eta(),1);
      fireJet8=true;
    }
    if (tj->pt()>52){
      hL1jetsEta12->Fill(tj->eta(),1);
      fireJet12=true;
    }
  }

  for (l1extra::L1JetParticleCollection::const_iterator tj=l1fjets->begin(); tj!=l1fjets->end(); tj++){
    if (tj->pt()>36){
      hL1jetsEta8->Fill(tj->eta(),1);
      fireJet8=true;
    }
    if (tj->pt()>52){
      fireJet12=true;
      hL1jetsEta12->Fill(tj->eta(),1);
    }
  }

  for (l1extra::L1JetParticleCollection::const_iterator tj=l1tjets->begin(); tj!=l1tjets->end(); tj++){
    if (tj->pt()>36){
      fireJet8=true;
      hL1jetsEta8->Fill(tj->eta(),1);
    }

    if (tj->pt()>52){
      fireJet12=true;
      hL1jetsEta12->Fill(tj->eta(),1);
    }
  }

  if (fireJet8&&fireJet8_fromGT) jetCrossTest8->Fill(0.1,1);   
  if (fireJet8&&!fireJet8_fromGT) jetCrossTest8->Fill(1.1,1);
  if (!fireJet8&&fireJet8_fromGT) jetCrossTest8->Fill(2.1,1);

  if (fireJet12&&fireJet12_fromGT) jetCrossTest12->Fill(0.1,1);
  if (fireJet12&&!fireJet12_fromGT) jetCrossTest12->Fill(1.1,1);
  if (!fireJet12&&fireJet12_fromGT) jetCrossTest12->Fill(2.1,1);

  if (useReco){
  
    //check calojets
    edm::Handle<reco::CaloJetCollection> cjets;
    iEvent.getByToken(caloJetTag, cjets);

    reco::CaloJetCollection::const_iterator i_cjet;

    for(i_cjet = cjets->begin(); i_cjet != cjets->end(); i_cjet++){
      if (i_cjet->eta()>3.5&&i_cjet->eta()<4.5){
         hCaloJetPlusET->Fill(i_cjet->pt(),1);
         if (fireJet8) hCaloJetPlusETtrig8->Fill(i_cjet->pt(),1);
         if (fireJet12) hCaloJetPlusETtrig12->Fill(i_cjet->pt(),1);
         if (fireHF1) hCaloJetPlusETtrigMB->Fill(i_cjet->pt(),1);
      }
      if (i_cjet->eta()>-4.5&&i_cjet->eta()<-3.5){
         hCaloJetMinusET->Fill(i_cjet->pt(),1);
         if (fireJet8) hCaloJetMinusETtrig8->Fill(i_cjet->pt(),1);
         if (fireJet12) hCaloJetMinusETtrig12->Fill(i_cjet->pt(),1);
         if (fireHF1) hCaloJetMinusETtrigMB->Fill(i_cjet->pt(),1);
      }
    }

    double etaLo[]={-5.0,-4.5,-4.0,-3.5,3.0,3.5,4.0,4.5};
    double etaHi[]={-4.5,-4.0,-3.5,-3.0,3.5,4.0,4.5,5.0};

    //check HF rechits
    edm::ESHandle<CaloGeometry> pG;
    iSetup.get<CaloGeometryRecord>().get(pG);
    geo = pG.product();

    edm::Handle<HFRecHitCollection> hfRHcol;
    iEvent.getByToken(hfRechitTag, hfRHcol);

    for (std::vector<HFRecHit>::const_iterator hhit=hfRHcol->begin(); hhit!=hfRHcol->end(); hhit++){
      /*
      //check that this hit was not considered before and push it into usedHits
      bool hitIsUsed=false;
      for (uint32_t i=0; i<usedHitsHC.size(); i++)
      {
      if (usedHitsHC[i]==hhit->id()) hitIsUsed=true;
      }
      if (hitIsUsed) continue;
      usedHitsHC.push_back(hhit->id());
      */
      ////////////
      GlobalPoint posH = geo->getPosition((*hhit).detid());
      //float phihit = posH.phi();
      float etahit = posH.eta();
      float e=hhit->energy();
      int hitdepth=hhit->id().depth();

      if (hitdepth==1){
       float etH=e; //*pow(cosh(etahit),-1);
       for (int ireg=0; ireg<8; ireg++){
          if (etahit>etaLo[ireg]&&etahit<etaHi[ireg]){
             hRecHitET[ireg]->Fill(etH,1);
             if (fireJet8) hRecHitETtrig8[ireg]->Fill(etH,1);
             if (fireJet12) hRecHitETtrig12[ireg]->Fill(etH,1);
             if (fireHF1) hRecHitETtrigMB[ireg]->Fill(etH,1);
          }
        }
      }
    }

    //check caloTowers
    edm::Handle<CaloTowerCollection> towers;
    iEvent.getByToken(caloTowerTag,towers);
    CaloTowerCollection::const_iterator cal;

    for ( cal = towers->begin(); cal != towers->end(); ++cal ){
      /*
      double eE     = cal->emEnergy();
      double eH     = cal->hadEnergy();
      double eHO    = cal->outerEnergy();
      */
      double etaT   = cal->eta();
      //       double phiT   = cal->phi();
      //       double en     = cal->energy();
      double etT    = cal->energy();//et();
      //       double had_tm = cal->hcalTime();
      //       double em_tm  = cal->ecalTime();
      for (int ireg=0; ireg<8; ireg++){
       if (etaT>etaLo[ireg]&&etaT<etaHi[ireg]){
          hCaloTowerET[ireg]->Fill(etT,1);
          if (fireJet8) hCaloTowerETtrig8[ireg]->Fill(etT,1);
          if (fireJet12) hCaloTowerETtrig12[ireg]->Fill(etT,1);
          if (fireHF1) hCaloTowerETtrigMB[ireg]->Fill(etT,1);
        }
      }
    }
  

  }//end of if useReco
}
// ------------ method called once each job just before starting event loop  ------------
void 
MBtriggerEfficiency::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
MBtriggerEfficiency::endJob() 
{
  outputFile->cd();
  accPerEvt->Scale(pow(evtsTot,-1));
  accPerEvt2sliceFront->Scale(pow(evtsTot,-1));
  accPerEvt2sliceBack->Scale(pow(evtsTot,-1));
  accPerEvtPlus->Scale(pow(evtsTot,-1));
  accPerEvtMinus->Scale(pow(evtsTot,-1));
  accPerEvtThrFile->Scale(pow(evtsTot,-1));
  amplVSsampl->Write();
  outputFile->mkdir("channels");
  outputFile->cd("channels");
  for (int i=0; i<26; i++)
    {
      for (int j=0; j<36; j++)
  {
  sig[0][i][j]->Write();
  sig[1][i][j]->Write();
//    sigPerChanLong[i][j]->Write();
//    sigPerChanShort[i][j]->Write();
  }
    }
  outputFile->cd();
  allChanSignalLong->Write();
  allChanSignalShort->Write();
  allChanSignal->Write();
  accPerEvt->Write();
  accPerEvt2sliceFront->Write();
  accPerEvt2sliceBack->Write();
  accPerEvtPlus->Write();
  accPerEvtMinus->Write();
  nChanLong->Write();
  nChanShort->Write();
  allChanEtaPhi->Write();
  sigProfile->Write();
  sigProfileShort->Write();
  sigAboveThr1->Write();
  sigAboveThrShort1->Write();

  chanAboveThrFileLong->Write();
  chanAboveThrFileShort->Write();
  accPerEvtThrFile->Write();

  idFired->TH1F::Sumw2();
  idFired->SetBinContent(1,evtsTot);
  idFired_frac->Add(idFired,pow(evtsTot,-1));
  idFired->Write();
  idFired_frac->Write();

  bxNum->Write();
  nMBHF1_firedBX->Write();
  nMBHF2_firedBX->Write();

  TH1F* HF1_OR_frac_vsLumi=new TH1F("HF1_OR_frac_vsLumi","HF1_OR_frac_vsLumi",1000,0,1000);
  TH1F* HF2_OR_frac_vsLumi=new TH1F("HF2_OR_frac_vsLumi","HF2_OR_frac_vsLumi",1000,0,1000);

  HF1_OR_vsLumi->TH1F::Sumw2();
  HF2_OR_vsLumi->TH1F::Sumw2();
  ZB_vsLumi->TH1F::Sumw2();

  HF1_OR_frac_vsLumi->Divide(HF1_OR_vsLumi,ZB_vsLumi,1,1,"B");
  HF2_OR_frac_vsLumi->Divide(HF2_OR_vsLumi,ZB_vsLumi,1,1,"B");

  ZB_vsLumi->Write();
  
  HF1_OR_frac_vsLumi->Write();
  HF2_OR_frac_vsLumi->Write();

  HF1_OR_vsLumi->Write();
  HF2_OR_vsLumi->Write();
  ZB_vsLumi->Write();

  crossTest_HF1->Write();
  crossTest_HF2->Write();
 
  jetCrossTest8->Write();
  jetCrossTest12->Write();

  hL1jetsEta8->Write();
  hL1jetsEta12->Write();
  
  TDirectory *ctdir = outputFile->mkdir("CaloTowers");
  ctdir->cd();
  TH1F* hCaloTower_TrigEff8[8];
  TH1F* hCaloTower_TrigEff12[8];
  TH1F* hCaloTower_TrigEffMB[8];
  char tmp[100];
  for (int i=0; i<8; i++)
    {
      hCaloTowerETtrig8[i]->TH1F::Sumw2();
      hCaloTowerETtrig12[i]->TH1F::Sumw2();
      hCaloTowerETtrigMB[i]->TH1F::Sumw2();
      hCaloTowerET[i]->TH1F::Sumw2();
      
      sprintf(tmp,"hCaloTower_TrigEff8_%d",i);
      hCaloTower_TrigEff8[i]=new TH1F(tmp,tmp,1000,0,1000);
      hCaloTower_TrigEff8[i]->Divide(hCaloTowerETtrig8[i],hCaloTowerET[i],1,1,"B");
      
      sprintf(tmp,"hCaloTower_TrigEff12_%d",i);
      hCaloTower_TrigEff12[i]=new TH1F(tmp,tmp,1000,0,1000);
      hCaloTower_TrigEff12[i]->Divide(hCaloTowerETtrig12[i],hCaloTowerET[i],1,1,"B");
      
      sprintf(tmp,"hCaloTower_TrigEffMB_%d",i);
      hCaloTower_TrigEffMB[i]=new TH1F(tmp,tmp,1000,0,1000);
      hCaloTower_TrigEffMB[i]->Divide(hCaloTowerETtrigMB[i],hCaloTowerET[i],1,1,"B");
      
      hCaloTowerET[i]->Write();
      hCaloTowerETtrig8[i]->Write();
      hCaloTowerETtrig12[i]->Write();
      hCaloTowerETtrigMB[i]->Write();
      hCaloTower_TrigEff8[i]->Write();
      hCaloTower_TrigEff12[i]->Write();
      hCaloTower_TrigEffMB[i]->Write();
    }

  TDirectory *rhdir = outputFile->mkdir("RecHits");
  rhdir->cd();
  TH1F* hRecHit_TrigEff8[8];
  TH1F* hRecHit_TrigEff12[8];
  TH1F* hRecHit_TrigEffMB[8];
  for (int i=0; i<8; i++)
    {
      hRecHitETtrigMB[i]->TH1F::Sumw2();
      hRecHitETtrig8[i]->TH1F::Sumw2();
      hRecHitETtrig12[i]->TH1F::Sumw2();
      hRecHitET[i]->TH1F::Sumw2();
      
      sprintf(tmp,"hRecHit_TrigEff8_%d",i);
      hRecHit_TrigEff8[i]=new TH1F(tmp,tmp,1000,0,1000);
      hRecHit_TrigEff8[i]->Divide(hRecHitETtrig8[i],hRecHitET[i],1,1,"B");
      
      sprintf(tmp,"hRecHit_TrigEff12_%d",i);
      hRecHit_TrigEff12[i]=new TH1F(tmp,tmp,1000,0,1000);
      hRecHit_TrigEff12[i]->Divide(hRecHitETtrig12[i],hRecHitET[i],1,1,"B");
      
      sprintf(tmp,"hRecHit_TrigEffMB_%d",i);
      hRecHit_TrigEffMB[i]=new TH1F(tmp,tmp,1000,0,1000);
      hRecHit_TrigEffMB[i]->Divide(hRecHitETtrigMB[i],hRecHitET[i],1,1,"B");

      hRecHitET[i]->Write();
      hRecHitETtrig8[i]->Write();
      hRecHitETtrig12[i]->Write();
      hRecHitETtrigMB[i]->Write();

      hRecHit_TrigEff8[i]->Write();
      hRecHit_TrigEff12[i]->Write();
      hRecHit_TrigEffMB[i]->Write();
    }

  TDirectory *cjdir = outputFile->mkdir("CaloJets");
  cjdir->cd();
  TH1F* hCaloJetPlus_TrigEff8=new TH1F("hCaloJetPlus_TrigEff8","hCaloJetPlus_TrigEff8",1000,0,1000);
  TH1F* hCaloJetPlus_TrigEff12=new TH1F("hCaloJetPlus_TrigEff12","hCaloJetPlus_TrigEff12",1000,0,1000);
  TH1F* hCaloJetPlus_TrigEffMB=new TH1F("hCaloJetPlus_TrigEffMB","hCaloJetPlus_TrigEffMB",1000,0,1000);

  TH1F* hCaloJetMinus_TrigEff8=new TH1F("hCaloJetMinus_TrigEff8","hCaloJetMinus_TrigEff8",1000,0,1000);
  TH1F* hCaloJetMinus_TrigEff12=new TH1F("hCaloJetMinus_TrigEff12","hCaloJetMinus_TrigEff12",1000,0,1000);
  TH1F* hCaloJetMinus_TrigEffMB=new TH1F("hCaloJetMinus_TrigEffMB","hCaloJetMinus_TrigEffMB",1000,0,1000);
      
  hCaloJetPlusETtrig8->TH1F::Sumw2();
  hCaloJetPlusETtrig12->TH1F::Sumw2();
  hCaloJetPlusETtrigMB->TH1F::Sumw2();
  hCaloJetPlusET->TH1F::Sumw2();
  
  hCaloJetMinusETtrig8->TH1F::Sumw2();
  hCaloJetMinusETtrig12->TH1F::Sumw2();
  hCaloJetMinusETtrigMB->TH1F::Sumw2();
  hCaloJetMinusET->TH1F::Sumw2();

  hCaloJetPlusETtrig8->Write();
  hCaloJetPlusETtrig12->Write();
  hCaloJetPlusETtrigMB->Write();
  hCaloJetPlusET->Write();

  hCaloJetMinusETtrig8->Write();
  hCaloJetMinusETtrig12->Write();
  hCaloJetMinusETtrigMB->Write();
  hCaloJetMinusET->Write();
  
  hCaloJetPlus_TrigEff8->Divide(hCaloJetPlusETtrig8, hCaloJetPlusET,1,1,"B");
  hCaloJetPlus_TrigEff12->Divide(hCaloJetPlusETtrig12, hCaloJetPlusET,1,1,"B");
  hCaloJetPlus_TrigEffMB->Divide(hCaloJetPlusETtrigMB, hCaloJetPlusET,1,1,"B");

  hCaloJetMinus_TrigEff8->Divide(hCaloJetMinusETtrig8, hCaloJetMinusET,1,1,"B");
  hCaloJetMinus_TrigEff12->Divide(hCaloJetMinusETtrig12, hCaloJetMinusET,1,1,"B");
  hCaloJetMinus_TrigEffMB->Divide(hCaloJetMinusETtrigMB, hCaloJetMinusET,1,1,"B");

  hCaloJetPlus_TrigEff8->Write();
  hCaloJetPlus_TrigEff12->Write();
  hCaloJetPlus_TrigEffMB->Write();

  hCaloJetMinus_TrigEff8->Write();
  hCaloJetMinus_TrigEff12->Write();
  hCaloJetMinus_TrigEffMB->Write();

  std::cout<<"wrote stuff"<<std::endl;
}

// ------------ method called when starting to processes a run  ------------

void 
MBtriggerEfficiency::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
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
MBtriggerEfficiency::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
MBtriggerEfficiency::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
MBtriggerEfficiency::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
MBtriggerEfficiency::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MBtriggerEfficiency);
