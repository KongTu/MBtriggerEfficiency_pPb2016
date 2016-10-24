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
#'/store/hidata/HIRun2015/HIMinimumBias1/RAW/v1/000/262/640/00000/10C1AEAA-F395-E511-AFB2-02163E013734.root'
#'/store/data/Run2016H/L1MinimumBias0/RAW/v1/000/281/616/00000/0EDB22AD-4983-E611-A03D-02163E0134FA.root'

#2016 Vdm LowPU
#'root://cmsxrootd.fnal.gov//store/data/Run2016B/ZeroBias/RAW/v2/000/273/589/00000/66E46879-2D1D-E611-A2F7-02163E011A1A.root'
#'root://cmsxrootd.fnal.gov//store/data/Run2016B/EmptyBX/RAW/v2/000/273/523/00000/18C906EF-561C-E611-AB79-02163E014489.root'

#2015:
#'root://cmsxrootd.fnal.gov//store/data/Run2015A/L1TechBPTXMinusOnly/RAW/v1/000/247/324/00000/0EE0B046-580D-E511-BB52-02163E0138F6.root'
#'root://cmsxrootd.fnal.gov//store/data/Run2015A/ZeroBias1/RAW/v1/000/247/324/00000/00C00730-A00D-E511-8273-02163E014565.root'

#Pythia8 test
#'file:/afs/cern.ch/work/z/ztu/Pythia/CMSSW_8_0_20/src/step3_RAW2DIGI_L1Reco_RECO_EI_PAT_DQM.root'

#2016 Cosmics run
'/store/express/Run2016H/ExpressCosmics/FEVT/Express-v2/000/283/595/00000/02EDC92B-C496-E611-8D08-02163E014616.root',
'/store/express/Run2016H/ExpressCosmics/FEVT/Express-v2/000/283/595/00000/0CBA6025-CB96-E611-9050-02163E011D3F.root',
'/store/express/Run2016H/ExpressCosmics/FEVT/Express-v2/000/283/595/00000/2C476B2E-C996-E611-9396-02163E014793.root',
'/store/express/Run2016H/ExpressCosmics/FEVT/Express-v2/000/283/595/00000/50EA1F24-C696-E611-9A76-02163E012139.root',
'/store/express/Run2016H/ExpressCosmics/FEVT/Express-v2/000/283/595/00000/5C93D236-C496-E611-A25B-02163E0121F9.root',
'/store/express/Run2016H/ExpressCosmics/FEVT/Express-v2/000/283/595/00000/7472B235-C696-E611-BD40-FA163E879C74.root',
'/store/express/Run2016H/ExpressCosmics/FEVT/Express-v2/000/283/595/00000/9E133DD8-CD96-E611-BA3A-02163E014361.root',
'/store/express/Run2016H/ExpressCosmics/FEVT/Express-v2/000/283/595/00000/9E2E6B0F-CB96-E611-AF28-02163E01187F.root',
'/store/express/Run2016H/ExpressCosmics/FEVT/Express-v2/000/283/595/00000/A038C228-C796-E611-8FDD-FA163E0D91FA.root',
'/store/express/Run2016H/ExpressCosmics/FEVT/Express-v2/000/283/595/00000/AECBE60A-CF96-E611-8C88-FA163E70A49C.root',
'/store/express/Run2016H/ExpressCosmics/FEVT/Express-v2/000/283/595/00000/BACFCB3E-C496-E611-913B-02163E013800.root',
'/store/express/Run2016H/ExpressCosmics/FEVT/Express-v2/000/283/595/00000/BE4F2E74-C696-E611-ACBE-02163E012A1E.root',
'/store/express/Run2016H/ExpressCosmics/FEVT/Express-v2/000/283/595/00000/CE0C7E11-CB96-E611-9C13-FA163EDCA8B3.root',
'/store/express/Run2016H/ExpressCosmics/FEVT/Express-v2/000/283/595/00000/CE8ECB08-C896-E611-AF2B-02163E0121F8.root',
'/store/express/Run2016H/ExpressCosmics/FEVT/Express-v2/000/283/595/00000/D066F832-C996-E611-800E-FA163E8EFA4E.root',
'/store/express/Run2016H/ExpressCosmics/FEVT/Express-v2/000/283/595/00000/D24FF934-C796-E611-996C-02163E013987.root',
'/store/express/Run2016H/ExpressCosmics/FEVT/Express-v2/000/283/595/00000/D4B99C21-C696-E611-BBEF-FA163E3EB1CE.root',
'/store/express/Run2016H/ExpressCosmics/FEVT/Express-v2/000/283/595/00000/EE4ABAC4-CD96-E611-A164-02163E011EBF.root',
'/store/express/Run2016H/ExpressCosmics/FEVT/Express-v2/000/283/595/00000/F6F97E2F-C996-E611-BA77-FA163E3AEC35.root',
'/store/express/Run2016H/ExpressCosmics/FEVT/Express-v2/000/283/595/00000/F8DF1FE4-CC96-E611-A194-02163E013787.root'
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
     #HLTPaths = cms.vstring('HLT_L1BptxPlus_v*'),
     #HLTPaths = cms.vstring('HLT_L1BptxMinus_v*'),
     #HLTPaths = cms.vstring('HLT_L1MinimumBiasHF_OR_part0_v2'),
     #HLTPaths = cms.vstring('HLT_HIL1Tech5_BPTX_PlusOnly_v1'),
     #HLTPaths = cms.vstring('HLT_HIL1Tech6_BPTX_MinusOnly_v1'),
     #HLTPaths = cms.vstring('HLT_HIZeroBias_v1'),
     HLTPaths = cms.vstring('HLT_Random_v*'),
     eventSetupPathsKey = cms.string(''),
     andOr = cms.bool(True),
     throw = cms.bool(False)
)

process.load("MBtriggerEfficiency_pPb2016.MBtriggerEfficiency.mbtriggerefficiency_cfi")

process.MBana.useBPTXplus = False
process.MBana.useBPTXminus = False
#process.MBana.beam1_empty_bx = [222,262,302,342,382,422,462,502,1112,1152,1192,1232,1272,1312,1352,1392,1432,1472,1512,1552,1800,1840,1880,1920,2344,2384,2424,2464,2504,2544,2584,2624,2794,2834,2874,2954,2994,3034,3074,3114,3154,3194,3234]
#process.MBana.beam2_empty_bx = [121,161,201,241,281,321,361,401,441,481,521,561,1450,1490,1530,1570,2003,2043,2083,2123,2163,2203,2243,2283,2323,2363,2403,2443,2691,2731,2771,2811,2892,2932,2972,3012,3052,3092,3132,3172]
process.MBana.beam1_empty_bx = [188,189,190,191,192,193,194,195,196,197,198,199]
process.MBana.beam2_empty_bx = [135,136,137,138,139,140,141,142,143,144,145,146]
process.MBana.selected_lumi = [0,10000]

process.load("PixelTrackFilter.PixelTrackFilter.pixelTrackfilter_cfi")
process.pixelTrackFilter.multMin = 1
process.pixelTrackFilter.doDS = True

#forHI data collection name
#process.hcalDigis.InputLabel = cms.InputTag('rawDataRepacker')
#process.ecalDigis.InputLabel = cms.InputTag('rawDataRepacker')
#process.ecalPreshowerDigis.sourceTag = cms.InputTag('rawDataRepacker')
##

process.p = cms.Path(   process.hcalDigis + process.ecalDigis + process.ecalPreshowerDigis 
			+ process.gtDigis 
			+ process.gctDigis 
			+ process.trigsel
			#+ process.pixelTrackFilter
			+ process.MBana
		    )

process.TFileService = cms.Service("TFileService",fileName = cms.string("test.root"))

