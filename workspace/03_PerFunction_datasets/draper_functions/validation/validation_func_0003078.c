getCalleeSavedRegs(const MachineFunction *MF) const {


  static const MCPhysReg CalleeSavedRegs[] = {
    XCore::R4, XCore::R5, XCore::R6, XCore::R7,
    XCore::R8, XCore::R9, XCore::R10,
    0
  };
  static const MCPhysReg CalleeSavedRegsFP[] = {
    XCore::R4, XCore::R5, XCore::R6, XCore::R7,
    XCore::R8, XCore::R9,
    0
  };
  const XCoreFrameLowering *TFI = getFrameLowering(*MF);
  if (TFI->hasFP(*MF))
    return CalleeSavedRegsFP;
  return CalleeSavedRegs;
}
