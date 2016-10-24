import FWCore.ParameterSet.Config as cms

MBana = cms.EDAnalyzer('MBtriggerEfficiency',
	useReco = cms.bool(False),
	useMC = cms.bool(False),
	doMultDepend = cms.bool(False),
	vertexSrc = cms.string("offlinePrimaryVertices"),
	trackSrc = cms.InputTag("generalTracks"),
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
	outputFileName=cms.string("test.root"),
	useBPTXplus = cms.bool(False),
	useBPTXminus = cms.bool(False),
	selected_lumi = cms.untracked.vint32(0,1000),
	beam1_empty_bx = cms.untracked.vint32(0,1,2,3,4,5,6,7,8,9),
	beam2_empty_bx = cms.untracked.vint32(0,1,2,3,4,5,6,7,8,9)

)
