DecodeL3RSrcDstInstruction(MCInst &Inst, unsigned Insn, uint64_t Address,
                           const void *Decoder) {
  unsigned Op1, Op2, Op3;
  DecodeStatus S =
  Decode3OpInstruction(fieldFromInstruction(Insn, 0, 16), Op1, Op2, Op3);
  if (S == MCDisassembler::Success) {
    DecodeGRRegsRegisterClass(Inst, Op1, Address, Decoder);
    DecodeGRRegsRegisterClass(Inst, Op1, Address, Decoder);
    DecodeGRRegsRegisterClass(Inst, Op2, Address, Decoder);
    DecodeGRRegsRegisterClass(Inst, Op3, Address, Decoder);
  }
  return S;
}
