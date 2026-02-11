ConvertInstTo3Addr(MachineBasicBlock::iterator &mi,
                                              MachineBasicBlock::iterator &nmi,
                                              MachineFunction::iterator &mbbi,
                                              unsigned RegB, unsigned Dist) {
  MachineInstr *NewMI = TII->convertToThreeAddress(mbbi, mi, LV);
  if (NewMI) {
    DEBUG(dbgs() << "2addr: CONVERTING 2-ADDR: " << *mi);
    DEBUG(dbgs() << "2addr:         TO 3-ADDR: " << *NewMI);
    bool Sunk = false;

    if (NewMI->findRegisterUseOperand(RegB, false, TRI))


      Sunk = Sink3AddrInstruction(mbbi, NewMI, RegB, mi);

    mbbi->erase(mi);

    if (!Sunk) {
      DistanceMap.insert(std::make_pair(NewMI, Dist));
      mi = NewMI;
      nmi = llvm::next(mi);
    }
    return true;
  }

  return false;
}
