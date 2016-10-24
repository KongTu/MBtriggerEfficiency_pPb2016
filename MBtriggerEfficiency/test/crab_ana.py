### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()
outputName = 'MBtriggerEfficiency_v18'
config.General.requestName = outputName
config.General.workArea = outputName
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.allowUndistributedCMSSW = True
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'mbtriggerefficiency_cfg.py'
#config.Data.inputDBS = 'global'
#MB
#config.Data.inputDataset = '/ZeroBias/Run2016H-v1/RAW'
config.Data.inputDataset = '/ZeroBias/Run2016H-PromptReco-v2/AOD'
#config.Data.inputDataset = '/EmptyBX/Run2016H-v1/RAW'
#config.Data.inputDataset = '/EmptyBX/Run2016H-PromptReco-v2/AOD'
#config.Data.inputDataset = '/L1MinimumBias0/Run2016H-PromptReco-v2/AOD'

#2016 VdM run
#config.Data.inputDataset = '/ZeroBias/Run2016B-v2/RAW'
#config.Data.inputDataset = '/EmptyBX/Run2016B-v2/RAW'

#2015 dNdeta
#config.Data.inputDataset = '/ZeroBias1/Run2015A-v1/RAW'
#config.Data.inputDataset = '/L1TechBPTXMinusOnly/Run2015A-v1/RAW'
#config.Data.inputDataset = '/L1TechBPTXPlusOnly/Run2015A-v1/RAW'

#2015PbPb
#config.Data.inputDataset = '/HIMinimumBias1/HIRun2015-v1/RAW'
#config.Data.userInputFiles = list(open('inputfile_262640.txt'))

config.Data.splitting = 'LumiBased'
config.Data.ignoreLocality = False
config.Data.unitsPerJob = 5
config.Data.useParent = True
config.Data.lumiMask = 'json_281616.txt'
#config.Data.lumiMask = 'json_247324.txt'
#config.Data.lumiMask = 'json_273523.txt'
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Site.storageSite = 'T2_US_MIT'
