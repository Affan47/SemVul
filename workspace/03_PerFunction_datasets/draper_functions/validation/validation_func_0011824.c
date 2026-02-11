printShiftImmOperand(const MCInst *MI, unsigned OpNum,
                                          const MCSubtargetInfo &STI,
                                          raw_ostream &O) {
  unsigned ShiftOp = MI->getOperand(OpNum).getImm();
  bool isASR = (ShiftOp & (1 << 5)) != 0;
  unsigned Amt = ShiftOp & 0x1f;
  if (isASR) {
    O << ", asr " << markup("<imm:") << "#" << (Amt == 0 ? 32 : Amt)
      << markup(">");
  } else if (Amt) {
    O << ", lsl " << markup("<imm:") << "#" << Amt << markup(">");
  }
}
