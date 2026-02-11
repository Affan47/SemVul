addPassesToGenerateCode(LLVMTargetMachine *TM, PassManagerBase &PM,
                        bool DisableVerify, AnalysisID StartBefore,
                        AnalysisID StartAfter, AnalysisID StopAfter,
                        MachineFunctionInitializer *MFInitializer = nullptr) {


  PM.add(createTargetTransformInfoWrapperPass(TM->getTargetIRAnalysis()));


  TargetPassConfig *PassConfig = TM->createPassConfig(PM);
  PassConfig->setStartStopPasses(StartBefore, StartAfter, StopAfter);


  PassConfig->setDisableVerify(DisableVerify);

  PM.add(PassConfig);

  PassConfig->addIRPasses();

  PassConfig->addCodeGenPrepare();

  PassConfig->addPassesToHandleExceptions();

  PassConfig->addISelPrepare();


  MachineModuleInfo *MMI = new MachineModuleInfo(
      *TM->getMCAsmInfo(), *TM->getMCRegisterInfo(), TM->getObjFileLowering());
  PM.add(MMI);


  PM.add(new MachineFunctionAnalysis(*TM, MFInitializer));


  if (EnableFastISelOption == cl::BOU_TRUE ||
      (TM->getOptLevel() == CodeGenOpt::None &&
       EnableFastISelOption != cl::BOU_FALSE))
    TM->setFastISel(true);


  if (PassConfig->addInstSelector())
    return nullptr;

  PassConfig->addMachinePasses();

  PassConfig->setInitialized();

  return &MMI->getContext();
}
