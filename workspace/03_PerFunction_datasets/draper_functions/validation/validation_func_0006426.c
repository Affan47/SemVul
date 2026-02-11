reserveIndirectRegisters(BitVector &Reserved,
                                             const MachineFunction &MF) const {
  const AMDGPUFrameLowering *TFL = static_cast<const AMDGPUFrameLowering *>(
      MF.getSubtarget().getFrameLowering());

  unsigned StackWidth = TFL->getStackWidth(MF);
  int End = getIndirectIndexEnd(MF);

  if (End == -1)
    return;

  for (int Index = getIndirectIndexBegin(MF); Index <= End; ++Index) {
    unsigned SuperReg = AMDGPU::R600_Reg128RegClass.getRegister(Index);
    Reserved.set(SuperReg);
    for (unsigned Chan = 0; Chan < StackWidth; ++Chan) {
      unsigned Reg = AMDGPU::R600_TReg32RegClass.getRegister((4 * Index) + Chan);
      Reserved.set(Reg);
    }
  }
}
