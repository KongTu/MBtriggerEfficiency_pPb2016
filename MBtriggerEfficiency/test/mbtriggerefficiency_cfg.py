import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('Demo',eras.Run2_2016)

#process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(

#'/store/data/Run2015D/ZeroBias/RAW/v1/000/259/152/00000/0C81667F-F672-E511-809D-02163E01440D.root' #2015 data, this works 
'/store/data/Run2016H/ZeroBias/RAW/v1/000/281/616/00000/10A691C2-3483-E611-AFD3-02163E012A9D.root' #2016 data, this DOESN'T work	
    )
)
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.load("Configuration.StandardSequences.Digi_cff")
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load("Configuration.EventContent.EventContent_cff")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.GlobalTag.globaltag = '80X_dataRun2_Prompt_v14'

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
     HLTPaths = cms.vstring('HLT_ZeroBias_v*'),
     eventSetupPathsKey = cms.string(''),
     andOr = cms.bool(True),
     throw = cms.bool(False)
)

process.load("MBtriggerEfficiency_pPb2016.MBtriggerEfficiency.mbtriggerefficiency_cfi")

process.p = cms.Path(   process.hcalDigis + process.ecalDigis + process.ecalPreshowerDigis 
			+ process.gtDigis 
			+ process.gctDigis 
			+ process.trigsel
			+ process.MBana)

process.TFileService = cms.Service("TFileService",fileName = cms.string("test.root"))

