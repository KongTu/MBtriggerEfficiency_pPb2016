import FWCore.ParameterSet.Config as cms

MBana = cms.EDAnalyzer('MBtriggerEfficiency',
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
