spillCalleeSavedRegisters(MachineBasicBlock &MBB,
                          MachineBasicBlock::iterator MI,
                          const std::vector<CalleeSavedInfo> &CSI,
                          const TargetRegisterInfo *TRI) const {
  MachineFunction *MF = MBB.getParent();
  MachineBasicBlock *EntryBlock = &MF->front();


  for (unsigned i = 0, e = CSI.size(); i != e; ++i) {


    unsigned Reg = CSI[i].getReg();
    bool IsRAAndRetAddrIsTaken = (Reg == Mips::RA)
      && MF->getFrameInfo()->isReturnAddressTaken();
    if (!IsRAAndRetAddrIsTaken)
      EntryBlock->addLiveIn(Reg);
  }

  return true;
}
