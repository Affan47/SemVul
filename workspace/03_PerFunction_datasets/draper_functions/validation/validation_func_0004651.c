FindFreeRegister(MachineBasicBlock::iterator MII,
                                 MachineBasicBlock &MBB,
                                 const TargetRegisterClass *RC,
                                 const TargetRegisterInfo *TRI,
                                 BitVector &AllocatableRegs) {
  BitVector Defs(TRI->getNumRegs());
  BitVector Uses(TRI->getNumRegs());
  SmallVector<unsigned, 4> LocalUses;
  SmallVector<unsigned, 4> Kills;


  unsigned Count = 0;
  while (Count < 2) {
    if (MII == MBB.begin())
      break;
    MachineInstr *PrevMI = prior(MII);
    MII = PrevMI;

    if (PrevMI->isDebugValue())
      continue;
    ++Count;

    for (unsigned i = 0, e = PrevMI->getNumOperands(); i != e; ++i) {
      MachineOperand &MO = PrevMI->getOperand(i);
      if (!MO.isReg() || MO.getReg() == 0)
        continue;
      unsigned Reg = MO.getReg();
      if (MO.isDef()) {
        Defs.set(Reg);
        for (const unsigned *AS = TRI->getAliasSet(Reg); *AS; ++AS)
          Defs.set(*AS);
      } else  {
        LocalUses.push_back(Reg);
        if (MO.isKill() && AllocatableRegs[Reg])
          Kills.push_back(Reg);
      }
    }

    for (unsigned i = 0, e = Kills.size(); i != e; ++i) {
      unsigned Kill = Kills[i];
      if (!Defs[Kill] && !Uses[Kill] &&
          RC->contains(Kill))
        return Kill;
    }
    for (unsigned i = 0, e = LocalUses.size(); i != e; ++i) {
      unsigned Reg = LocalUses[i];
      Uses.set(Reg);
      for (const unsigned *AS = TRI->getAliasSet(Reg); *AS; ++AS)
        Uses.set(*AS);
    }
  }

  return 0;
}
