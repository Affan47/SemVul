runOnMachineFunction(MachineFunction &mf) {
  DEBUG(dbgs() << "********** GREEDY REGISTER ALLOCATION **********\n"
               << "********** Function: " << mf.getName() << '\n');

  MF = &mf;
  TRI = MF->getSubtarget().getRegisterInfo();
  TII = MF->getSubtarget().getInstrInfo();
  RCI.runOnMachineFunction(mf);

  EnableLocalReassign = EnableLocalReassignment ||
                        MF->getSubtarget().enableRALocalReassignment(
                            MF->getTarget().getOptLevel());

  if (VerifyEnabled)
    MF->verify(this, "Before greedy register allocator");

  RegAllocBase::init(getAnalysis<VirtRegMap>(),
                     getAnalysis<LiveIntervals>(),
                     getAnalysis<LiveRegMatrix>());
  Indexes = &getAnalysis<SlotIndexes>();
  MBFI = &getAnalysis<MachineBlockFrequencyInfo>();
  DomTree = &getAnalysis<MachineDominatorTree>();
  SpillerInstance.reset(createInlineSpiller(*this, *MF, *VRM));
  Loops = &getAnalysis<MachineLoopInfo>();
  Bundles = &getAnalysis<EdgeBundles>();
  SpillPlacer = &getAnalysis<SpillPlacement>();
  DebugVars = &getAnalysis<LiveDebugVariables>();

  initializeCSRCost();

  calculateSpillWeightsAndHints(*LIS, mf, VRM, *Loops, *MBFI);

  DEBUG(LIS->dump());

  SA.reset(new SplitAnalysis(*VRM, *LIS, *Loops));
  SE.reset(new SplitEditor(*SA, *LIS, *VRM, *DomTree, *MBFI));
  ExtraRegInfo.clear();
  ExtraRegInfo.resize(MRI->getNumVirtRegs());
  NextCascade = 1;
  IntfCache.init(MF, Matrix->getLiveUnions(), Indexes, LIS, TRI);
  GlobalCand.resize(32);
  SetOfBrokenHints.clear();

  allocatePhysRegs();
  tryHintsRecoloring();
  releaseMemory();
  return true;
}
