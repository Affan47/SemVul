DecodeSORegImmOperand(MCInst &Inst, unsigned Val,
                               uint64_t Address, const void *Decoder) {
  DecodeStatus S = MCDisassembler::Success;

  unsigned Rm = fieldFromInstruction(Val, 0, 4);
  unsigned type = fieldFromInstruction(Val, 5, 2);
  unsigned imm = fieldFromInstruction(Val, 7, 5);


  if (!Check(S, DecoderGPRRegisterClass(Inst, Rm, Address, Decoder)))
    return MCDisassembler::Fail;

  ARM_AM::ShiftOpc Shift = ARM_AM::lsl;
  switch (type) {
    case 0:
      Shift = ARM_AM::lsl;
      break;
    case 1:
      Shift = ARM_AM::lsr;
      break;
    case 2:
      Shift = ARM_AM::asr;
      break;
    case 3:
      Shift = ARM_AM::ror;
      break;
  }

  if (Shift == ARM_AM::ror && imm == 0)
    Shift = ARM_AM::rrx;

  unsigned Op = Shift | (imm << 3);
  Inst.addOperand(MCOperand::createImm(Op));

  return S;
}
