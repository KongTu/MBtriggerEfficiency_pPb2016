import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('Demo',eras.Run2_2016)

#process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(

#'/store/data/Run2016H/ZeroBias/RAW/v1/000/281/616/00000/10A691C2-3483-E611-AFD3-02163E012A9D.root' #2016 data, this DOESN'T work	
#'/store/data/Run2016H/EmptyBX/RAW/v1/000/281/616/00000/00FBDE35-4883-E611-8CFC-02163E01384C.root'
#'root://cmsxrootd.fnal.gov//store/data/Run2016H/EmptyBX/RAW/v1/000/281/616/00000/00FBDE35-4883-E611-8CFC-02163E01384C.root'
'/store/hidata/HIRun2015/HIMinimumBias1/RAW/v1/000/262/640/00000/10C1AEAA-F395-E511-AFB2-02163E013734.root'
#'/store/data/Run2016H/L1MinimumBias0/RAW/v1/000/281/616/00000/0EDB22AD-4983-E611-A03D-02163E0134FA.root'

#2015:
#'root://cmsxrootd.fnal.gov//store/data/Run2015A/L1TechBPTXMinusOnly/RAW/v1/000/247/324/00000/0EE0B046-580D-E511-BB52-02163E0138F6.root'
#'root://cmsxrootd.fnal.gov//store/data/Run2015A/ZeroBias1/RAW/v1/000/247/324/00000/00C00730-A00D-E511-8273-02163E014565.root'
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
     #HLTPaths = cms.vstring('HLT_ZeroBias_v*'),
     #HLTPaths = cms.vstring('HLT_L1BptxPlus_v2'),
     #HLTPaths = cms.vstring('HLT_L1MinimumBiasHF_OR_part0_v2'),
     #HLTPaths = cms.vstring('HLT_HIL1Tech5_BPTX_PlusOnly_v1'),
     HLTPaths = cms.vstring('HLT_HIL1Tech6_BPTX_MinusOnly_v1'),
     #HLTPaths = cms.vstring('HLT_HIZeroBias_v1'),
     eventSetupPathsKey = cms.string(''),
     andOr = cms.bool(False),
     throw = cms.bool(False)
)

process.load("MBtriggerEfficiency_pPb2016.MBtriggerEfficiency.mbtriggerefficiency_cfi")

process.MBana.useBPTXplus = False
process.MBana.useBPTXminus = False
process.MBana.beam1_empty_bx = [188,189,190,191,192,193,194,195,196,197,198,199]
process.MBana.beam2_empty_bx = [135,136,137,138,139,140,141,142,143,144,145,146]
process.MBana.selected_lumi = [87,102,105,232]

process.load("PixelTrackFilter.PixelTrackFilter.pixelTrackfilter_cfi")
process.pixelTrackFilter.multMin = 1

#forHI data collection name
process.hcalDigis.InputLabel = cms.InputTag('rawDataRepacker')
process.ecalDigis.InputLabel = cms.InputTag('rawDataRepacker')
process.ecalPreshowerDigis.sourceTag = cms.InputTag('rawDataRepacker')
##

process.p = cms.Path(   process.hcalDigis + process.ecalDigis + process.ecalPreshowerDigis 
			+ process.gtDigis 
			+ process.gctDigis 
			+ process.trigsel
			#+ process.pixelTrackFilter
			+ process.MBana
		    )

process.TFileService = cms.Service("TFileService",fileName = cms.string("test.root"))

