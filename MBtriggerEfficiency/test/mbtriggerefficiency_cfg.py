import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(30000) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
#dNdEta run

#zerobias2
'/store/data/Run2015A/ZeroBias1/RAW/v1/000/247/920/00000/00C32415-C911-E511-9520-02163E0142B9.root',
'/store/data/Run2015A/ZeroBias1/RAW/v1/000/247/920/00000/080C38EB-8312-E511-AC02-02163E013654.root',
'/store/data/Run2015A/ZeroBias1/RAW/v1/000/247/920/00000/0844A503-C711-E511-BF89-02163E014528.root',
'/store/data/Run2015A/ZeroBias1/RAW/v1/000/247/920/00000/0EB92E71-8711-E511-A79D-02163E014458.root',
'/store/data/Run2015A/ZeroBias1/RAW/v1/000/247/920/00000/10072A05-8412-E511-84DC-02163E012B9A.root',
'/store/data/Run2015A/ZeroBias1/RAW/v1/000/247/920/00000/10268A8D-8711-E511-97F4-02163E0144CF.root',
'/store/data/Run2015A/ZeroBias1/RAW/v1/000/247/920/00000/1A2E50A8-8412-E511-9A54-02163E0135FA.root',
'/store/data/Run2015A/ZeroBias1/RAW/v1/000/247/920/00000/1A3145A4-8711-E511-8C58-02163E0145D1.root',
'/store/data/Run2015A/ZeroBias1/RAW/v1/000/247/920/00000/1E4005E8-8312-E511-B745-02163E011929.root',
'/store/data/Run2015A/ZeroBias1/RAW/v1/000/247/920/00000/24373704-8412-E511-B503-02163E013829.root',
'/store/data/Run2015A/ZeroBias1/RAW/v1/000/247/920/00000/24BB49EB-8312-E511-A87E-02163E013907.root',
'/store/data/Run2015A/ZeroBias1/RAW/v1/000/247/920/00000/366E75FF-8312-E511-992E-02163E011A1A.root',
'/store/data/Run2015A/ZeroBias1/RAW/v1/000/247/920/00000/42476C16-C911-E511-9781-02163E014698.root',
'/store/data/Run2015A/ZeroBias1/RAW/v1/000/247/920/00000/443F9504-8111-E511-887F-02163E013477.root',
'/store/data/Run2015A/ZeroBias1/RAW/v1/000/247/920/00000/4C0E9A7E-8E12-E511-BC8B-02163E013584.root'
	)
)

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
#from Configuration.AlCa.autoCond import autoCond
#process.GlobalTag.globaltag = 'GR_P_V54::All'
process.GlobalTag.globaltag = 'GR_P_V56::All'
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
process.es_prefer_es_pool = cms.ESPrefer( "PoolDBESSource", "es_pool" )

# override the L1 menu from an Xml file
process.l1GtTriggerMenuXml = cms.ESProducer("L1GtTriggerMenuXmlProducer",
  TriggerMenuLuminosity = cms.string('startup'),
  DefXmlFile = cms.string('L1Menu_Collisions2015_lowPU_v3_L1T_Scales_20141121.xml'), 
  VmeXmlFile = cms.string('')
)
process.L1GtTriggerMenuRcdSource = cms.ESSource("EmptyESSource",
  recordName = cms.string('L1GtTriggerMenuRcd'),
  iovIsRunNotTime = cms.bool(True),
  firstValid = cms.vuint32(1)
)
process.es_prefer_l1GtParameters = cms.ESPrefer('L1GtTriggerMenuXmlProducer','l1GtTriggerMenuXml')


process.load("Configuration.Geometry.GeometryDB_cff")
process.load("Configuration.StandardSequences.RawToDigi_Data_cff")

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
	gtDigiTag=cms.InputTag("gtDigis"),
	gctDigiTag=cms.InputTag("gctDigis"),
	caloTowerTag=cms.InputTag("towerMaker"),
	caloJetTag=cms.InputTag("ak4CaloJets"),
	hfRechitTag=cms.InputTag("hfreco"),
	outputFileName=cms.string("output_247920_all.root")
)

process.p = cms.Path(process.hcalDigis + process.ecalDigis + process.ecalPreshowerDigis + process.gtDigis + process.gctDigis + process.L1Extra + process.digian)

#process.ep = cms.EndPath(process.output)
