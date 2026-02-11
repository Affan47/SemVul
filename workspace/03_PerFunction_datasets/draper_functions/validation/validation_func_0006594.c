EmitDwarfRegOp(const MachineLocation &MLoc) const {
  const TargetRegisterInfo *TRI = TM.getRegisterInfo();
  int Reg = TRI->getDwarfRegNum(MLoc.getReg(), false);

  for (const unsigned *SR = TRI->getSuperRegisters(MLoc.getReg());
       *SR && Reg < 0; ++SR) {
    Reg = TRI->getDwarfRegNum(*SR, false);


  }


  if (int Offset =  MLoc.getOffset()) {
    if (Reg < 32) {
      OutStreamer.AddComment(
        dwarf::OperationEncodingString(dwarf::DW_OP_breg0 + Reg));
      EmitInt8(dwarf::DW_OP_breg0 + Reg);
    } else {
      OutStreamer.AddComment("DW_OP_bregx");
      EmitInt8(dwarf::DW_OP_bregx);
      OutStreamer.AddComment(Twine(Reg));
      EmitULEB128(Reg);
    }
    EmitSLEB128(Offset);
  } else {
    if (Reg < 32) {
      OutStreamer.AddComment(
        dwarf::OperationEncodingString(dwarf::DW_OP_reg0 + Reg));
      EmitInt8(dwarf::DW_OP_reg0 + Reg);
    } else {
      OutStreamer.AddComment("DW_OP_regx");
      EmitInt8(dwarf::DW_OP_regx);
      OutStreamer.AddComment(Twine(Reg));
      EmitULEB128(Reg);
    }
  }


}
