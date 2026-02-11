findCommutedOpIndices(MachineInstr *MI,
                                        unsigned &SrcOpIdx0,
                                        unsigned &SrcOpIdx1) const {
  const MCInstrDesc &MCID = MI->getDesc();
  if (!MCID.isCommutable())
    return false;

  unsigned Opc = MI->getOpcode();
  int Src0Idx = AMDGPU::getNamedOperandIdx(Opc, AMDGPU::OpName::src0);
  if (Src0Idx == -1)
    return false;


  if (!MI->getOperand(Src0Idx).isReg())
    return false;

  int Src1Idx = AMDGPU::getNamedOperandIdx(Opc, AMDGPU::OpName::src1);
  if (Src1Idx == -1)
    return false;

  MachineOperand &Src1 = MI->getOperand(Src1Idx);
  if (Src1.isImm()) {


    if (!isVOP2(MI->getOpcode()) && !isVOP3(MI->getOpcode()))
      return false;
  } else if (Src1.isReg()) {


    if (hasModifiersSet(*MI, AMDGPU::OpName::src0_modifiers) ||
        hasModifiersSet(*MI, AMDGPU::OpName::src1_modifiers))
      return false;
  } else
    return false;

  return fixCommutedOpIndices(SrcOpIdx0, SrcOpIdx1, Src0Idx, Src1Idx);
}
