CountTerminators(MachineBasicBlock *MBB,
                                 MachineBasicBlock::iterator &I) {
  I = MBB->end();
  unsigned NumTerms = 0;
  for (;;) {
    if (I == MBB->begin()) {
      I = MBB->end();
      break;
    }
    --I;
    if (!I->isTerminator()) break;
    ++NumTerms;
  }
  return NumTerms;
}
