migrateInstruction(MachineBasicBlock *SrcMBB,
    MachineBasicBlock *DstMBB, MachineBasicBlock::iterator I) {
  MachineBasicBlock::iterator SpliceEnd;

  MachineInstr *BranchMI = getNormalBlockBranchInstr(SrcMBB);
  if (!BranchMI) {
    DEBUG(
      dbgs() << "migrateInstruction don't see branch instr\n" ;
    );
    SpliceEnd = SrcMBB->end();
  } else {
    DEBUG(dbgs() << "migrateInstruction see branch instr: " << *BranchMI);
    SpliceEnd = BranchMI;
  }
  DEBUG(
    dbgs() << "migrateInstruction before splice dstSize = " << DstMBB->size()
      << "srcSize = " << SrcMBB->size() << "\n";
  );


  DstMBB->splice(I, SrcMBB, SrcMBB->begin(), SpliceEnd);

  DEBUG(
    dbgs() << "migrateInstruction after splice dstSize = " << DstMBB->size()
      << "srcSize = " << SrcMBB->size() << '\n';
  );
}
