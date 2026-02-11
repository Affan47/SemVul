getAddrModeUPBits(unsigned Mode) {
  unsigned Binary = 0;


  switch (Mode) {
  default: llvm_unreachable("Unknown addressing sub-mode!");
  case ARM_AM::da:                                     break;
  case ARM_AM::db: Binary |= 0x1 << ARMII::P_BitShift; break;
  case ARM_AM::ia: Binary |= 0x1 << ARMII::U_BitShift; break;
  case ARM_AM::ib: Binary |= 0x3 << ARMII::U_BitShift; break;
  }

  return Binary;
}
