SplitPHIEdges(MachineFunction &MF,
                                   MachineBasicBlock &MBB,
                                   MachineLoopInfo *MLI) {
  if (MBB.empty() || !MBB.front().isPHI() || MBB.isEHPad())
    return false;

  const MachineLoop *CurLoop = MLI ? MLI->getLoopFor(&MBB) : nullptr;
  bool IsLoopHeader = CurLoop && &MBB == CurLoop->getHeader();

  bool Changed = false;
  for (MachineBasicBlock::iterator BBI = MBB.begin(), BBE = MBB.end();
       BBI != BBE && BBI->isPHI(); ++BBI) {
    for (unsigned i = 1, e = BBI->getNumOperands(); i != e; i += 2) {
      unsigned Reg = BBI->getOperand(i).getReg();
      MachineBasicBlock *PreMBB = BBI->getOperand(i+1).getMBB();

      if (PreMBB->succ_size() == 1)
        continue;


      if (PreMBB == &MBB && !SplitAllCriticalEdges)
        continue;
      const MachineLoop *PreLoop = MLI ? MLI->getLoopFor(PreMBB) : nullptr;
      if (IsLoopHeader && PreLoop == CurLoop && !SplitAllCriticalEdges)
        continue;


      bool ShouldSplit = isLiveOutPastPHIs(Reg, PreMBB);
      if (!ShouldSplit && !NoPhiElimLiveOutEarlyExit)
        continue;
      if (ShouldSplit) {
        DEBUG(dbgs() << PrintReg(Reg) << " live-out before critical edge BB#"
                     << PreMBB->getNumber() << " -> BB#" << MBB.getNumber()
                     << ": " << *BBI);
      }


      ShouldSplit = ShouldSplit && !isLiveIn(Reg, &MBB);


      if (!ShouldSplit && CurLoop != PreLoop) {
        DEBUG({
          dbgs() << "Split wouldn't help, maybe avoid loop copies?\n";
          if (PreLoop) dbgs() << "PreLoop: " << *PreLoop;
          if (CurLoop) dbgs() << "CurLoop: " << *CurLoop;
        });


        ShouldSplit = PreLoop && !PreLoop->contains(CurLoop);
      }
      if (!ShouldSplit && !SplitAllCriticalEdges)
        continue;
      if (!PreMBB->SplitCriticalEdge(&MBB, this)) {
        DEBUG(dbgs() << "Failed to split critical edge.\n");
        continue;
      }
      Changed = true;
      ++NumCriticalEdgesSplit;
    }
  }
  return Changed;
}
