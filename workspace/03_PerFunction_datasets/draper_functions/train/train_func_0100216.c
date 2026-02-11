insertNoop(MachineBasicBlock &MBB,
                              MachineBasicBlock::iterator MI) const {


  unsigned Directive = Subtarget.getDarwinDirective();
  unsigned Opcode;
  switch (Directive) {
  default:            Opcode = PPC::NOP; break;
  case PPC::DIR_PWR6: Opcode = PPC::NOP_GT_PWR6; break;
  case PPC::DIR_PWR7: Opcode = PPC::NOP_GT_PWR7; break;
  case PPC::DIR_PWR8: Opcode = PPC::NOP_GT_PWR7; break;
  }

  DebugLoc DL;
  BuildMI(MBB, MI, DL, get(Opcode));
}
