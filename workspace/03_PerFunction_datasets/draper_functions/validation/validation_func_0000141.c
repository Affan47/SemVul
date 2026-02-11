DecodeT2LoadLabel(MCInst &Inst, unsigned Insn,
                                uint64_t Address, const void* Decoder) {
  DecodeStatus S = MCDisassembler::Success;

  unsigned Rt = fieldFromInstruction(Insn, 12, 4);
  unsigned U = fieldFromInstruction(Insn, 23, 1);
  int imm = fieldFromInstruction(Insn, 0, 12);

  const FeatureBitset &featureBits =
    ((const MCDisassembler*)Decoder)->getSubtargetInfo().getFeatureBits();

  bool hasV7Ops = featureBits[ARM::HasV7Ops];

  if (Rt == 15) {
    switch (Inst.getOpcode()) {
      case ARM::t2LDRBpci:
      case ARM::t2LDRHpci:
        Inst.setOpcode(ARM::t2PLDpci);
        break;
      case ARM::t2LDRSBpci:
        Inst.setOpcode(ARM::t2PLIpci);
        break;
      case ARM::t2LDRSHpci:
        return MCDisassembler::Fail;
      default:
        break;
    }
  }

  switch(Inst.getOpcode()) {
  case ARM::t2PLDpci:
    break;
  case ARM::t2PLIpci:
    if (!hasV7Ops)
      return MCDisassembler::Fail;
    break;
  default:
    if (!Check(S, DecodeGPRRegisterClass(Inst, Rt, Address, Decoder)))
      return MCDisassembler::Fail;
  }

  if (!U) {

    if (imm == 0)
      imm = INT32_MIN;
    else
      imm = -imm;
  }
  Inst.addOperand(MCOperand::createImm(imm));

  return S;
}
