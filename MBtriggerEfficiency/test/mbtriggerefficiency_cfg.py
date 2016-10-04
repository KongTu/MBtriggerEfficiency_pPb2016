import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('Demo',eras.Run2_2016)

#process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(

#'/store/data/Run2015D/ZeroBias/RAW/v1/000/259/152/00000/0C81667F-F672-E511-809D-02163E01440D.root'
#'/store/data/Run2016H/ZeroBias/RAW/v1/000/281/616/00000/10A691C2-3483-E611-AFD3-02163E012A9D.root'
'/store/data/Run2016H/ZeroBias/RAW/v1/000/281/616/00000/10A691C2-3483-E611-AFD3-02163E012A9D.root'	
#'/store/data/Run2016D/ZeroBias/RAW/v2/000/276/582/00000/04805A7E-3247-E611-AF3C-02163E011B83.root'
#'/store/data/Run2016H/ZeroBias/RAW/v1/000/281/638/00000/1EB0A26D-BF83-E611-A184-02163E012507.root'
    )
)


process.load('Configuration.StandardSequences.Services_cff')
process.load("Configuration.StandardSequences.Digi_cff")
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load("Configuration.StandardSequences.RawToDigi_cff")
process.load("Configuration.EventContent.EventContent_cff")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
#from Configuration.AlCa.autoCond import autoCond
#process.GlobalTag.globaltag = 'GR_P_V54::All'
#process.GlobalTag.globaltag = 'GR_P_V56::All'
process.GlobalTag.globaltag = '80X_dataRun2_Prompt_v14'
#process.GlobalTag.globaltag = 'GR_H_V58C::All'
#process.GlobalTag.globaltag = 'GR_E_V49::All'
#autoCond['com15'] ## == GR_R_53_V16::All in 5_3_7

#process.GlobalTag.connect=cms.string('frontier://FrontierInt/CMS_CONDITIONS')

#   For the uTCA map
process.es_pool = cms.ESSource("PoolDBESSource",
       process.CondDBSetup,
       timetype = cms.string('runnumber'),
       toGet = cms.VPSet(
           cms.PSet(
                   record = cms.string("HcalElectronicsMapRcd"),
                   tag = cms.string("HcalElectronicsMap_v7.05_offline")
               )
           ),
       connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS'),
               authenticationMethod = cms.untracked.uint32(0)
)

#process.load('CondCore.CondDB.CondDB_cfi')
#process.CondDB.connect = 'frontier://FrontierProd/CMS_CONDITIONS'
#process.es_pool = cms.ESSource("PoolDBESSource",

#	process.CondDB,
#    		toGet = cms.VPSet(cms.PSet(
#        	record = cms.string("HcalElectronicsMapRcd"),
#        	tag = cms.string("HcalElectronicsMap_v7.05_offline")
#    	))
#)

process.es_prefer_es_pool = cms.ESPrefer( "PoolDBESSource", "es_pool" )

# override the L1 menu from an Xml file
process.l1GtTriggerMenuXml = cms.ESProducer("L1GtTriggerMenuXmlProducer",
  TriggerMenuLuminosity = cms.string('startup'),
  DefXmlFile = cms.string('L1Menu_Collisions2015_lowPU_v4_L1T_Scales_20141121.xml'), 
  #DefXmlFile = cms.string('L1Menu_Collisions2016_v7_m2.xml'),
  VmeXmlFile = cms.string('')
)
process.L1GtTriggerMenuRcdSource = cms.ESSource("EmptyESSource",
  recordName = cms.string('L1GtTriggerMenuRcd'),
  iovIsRunNotTime = cms.bool(True),
  firstValid = cms.vuint32(1)
)
process.es_prefer_l1GtParameters = cms.ESPrefer('L1GtTriggerMenuXmlProducer','l1GtTriggerMenuXml')


process.load("Configuration.Geometry.GeometryDB_cff")
process.load("Configuration.StandardSequences.RawToDigi_cff")
process.load('L1Trigger.Configuration.L1Extra_cff')

# replacing arguments for L1Extra
process.l1extraParticles.muonSource = cms.InputTag('gtDigis')
process.l1extraParticles.isolatedEmSource = cms.InputTag('gctDigis', 'isoEm')
process.l1extraParticles.nonIsolatedEmSource = cms.InputTag('gctDigis', 'nonIsoEm')
process.l1extraParticles.centralJetSource = cms.InputTag('gctDigis', 'cenJets')
process.l1extraParticles.forwardJetSource = cms.InputTag('gctDigis', 'forJets')
process.l1extraParticles.tauJetSource = cms.InputTag('gctDigis', 'tauJets')
process.l1extraParticles.etTotalSource = cms.InputTag('gctDigis')
process.l1extraParticles.etHadSource = cms.InputTag('gctDigis')
process.l1extraParticles.etMissSource = cms.InputTag('gctDigis')
process.l1extraParticles.htMissSource = cms.InputTag("gctDigis")
process.l1extraParticles.hfRingEtSumsSource = cms.InputTag("gctDigis")
process.l1extraParticles.hfRingBitCountsSource = cms.InputTag("gctDigis")

#process.hcalDigis.InputLabel = cms.InputTag("source")

process.options = cms.untracked.PSet(
#    Rethrow = cms.untracked.vstring('ProductNotFound'),
    wantSummary=cms.untracked.bool(True)
)

# Output definition
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring(
        'keep *'
     ), 
    fileName = cms.untracked.string('outProd.root')
)

process.TFileService = cms.Service("TFileService",fileName = cms.string("test.root"))

process.trigsel = cms.EDFilter("HLTHighLevel",
     TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
     HLTPaths = cms.vstring('HLT_ZeroBias_v1'),
     eventSetupPathsKey = cms.string(''),
     andOr = cms.bool(True),
     throw = cms.bool(False)
)

process.load("Configuration.StandardSequences.Reconstruction_cff")

process.digian = cms.EDAnalyzer('MBtriggerEfficiency',
	useReco = cms.bool(False),
	useMC = cms.bool(False),
	l1GtRecordInputTag = cms.InputTag("gtDigis"),
        l1GtReadoutRecordInputTag = cms.InputTag("gtDigis"),
        l1GtTriggerMenuLiteInputTag = cms.InputTag("gtDigis"),
	m_l1CenJetToken = cms.InputTag("l1extraParticles","Central"),
     	m_l1ForJetToken = cms.InputTag("l1extraParticles","Forward"),
	m_l1TauJetToken = cms.InputTag("l1extraParticles","Tau"),
        hfDigiTag = cms.InputTag("hcalDigis"),
        gtDigiToken = cms.InputTag("gtDigis"),
        gtDigiTag=cms.InputTag("gtDigis"),
	gctDigiTag=cms.InputTag("gctDigis"),
	caloTowerTag=cms.InputTag("towerMaker"),
	caloJetTag=cms.InputTag("ak4CaloJets"),
	hfRechitTag=cms.InputTag("hfreco"),
	outputFileName=cms.string("test.root")
)

process.p = cms.Path(process.hcalDigis + process.ecalDigis + process.ecalPreshowerDigis + process.gtDigis + process.gctDigis + process.L1Extra + process.digian)



#process.ep = cms.EndPath(process.output)
