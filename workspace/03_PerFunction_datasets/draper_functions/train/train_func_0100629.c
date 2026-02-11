getAnalysisUsage(AnalysisUsage &AU) const {
  AU.setPreservesCFG();
  AU.addRequired<AliasAnalysis>();
  AU.addPreserved<AliasAnalysis>();
  AU.addRequired<LiveVariables>();
  AU.addPreserved<LiveVariables>();
  AU.addRequired<MachineLoopInfo>();
  AU.addPreserved<MachineLoopInfo>();
  AU.addPreservedID(MachineDominatorsID);

  if (!StrongPHIElim) {
    AU.addPreservedID(PHIEliminationID);
    AU.addRequiredID(PHIEliminationID);
  }

  AU.addRequiredID(TwoAddressInstructionPassID);
  AU.addPreserved<ProcessImplicitDefs>();
  AU.addRequired<ProcessImplicitDefs>();
  AU.addPreserved<SlotIndexes>();
  AU.addRequiredTransitive<SlotIndexes>();
  MachineFunctionPass::getAnalysisUsage(AU);
}
