emitSPUpdate(MachineBasicBlock &MBB, MachineBasicBlock::iterator &MBBI,
                  unsigned StackPtr, int64_t NumBytes,
                  bool Is64Bit, const TargetInstrInfo &TII,
                  const TargetRegisterInfo &TRI) {
  bool isSub = NumBytes < 0;
  uint64_t Offset = isSub ? -NumBytes : NumBytes;
  unsigned Opc = isSub ?
    getSUBriOpcode(Is64Bit, Offset) :
    getADDriOpcode(Is64Bit, Offset);
  uint64_t Chunk = (1LL << 31) - 1;
  DebugLoc DL = MBB.findDebugLoc(MBBI);

  while (Offset) {
    uint64_t ThisVal = (Offset > Chunk) ? Chunk : Offset;
    if (ThisVal == (Is64Bit ? 8 : 4)) {

      unsigned Reg = isSub
        ? (unsigned)(Is64Bit ? X86::RAX : X86::EAX)
        : findDeadCallerSavedReg(MBB, MBBI, TRI, Is64Bit);
      if (Reg) {
        Opc = isSub
          ? (Is64Bit ? X86::PUSH64r : X86::PUSH32r)
          : (Is64Bit ? X86::POP64r  : X86::POP32r);
        MachineInstr *MI = BuildMI(MBB, MBBI, DL, TII.get(Opc))
          .addReg(Reg, getDefRegState(!isSub) | getUndefRegState(isSub));
        if (isSub)
          MI->setFlag(MachineInstr::FrameSetup);
        Offset -= ThisVal;
        continue;
      }
    }

    MachineInstr *MI =
      BuildMI(MBB, MBBI, DL, TII.get(Opc), StackPtr)
      .addReg(StackPtr)
      .addImm(ThisVal);
    if (isSub)
      MI->setFlag(MachineInstr::FrameSetup);
    MI->getOperand(3).setIsDead();
    Offset -= ThisVal;
  }
}
