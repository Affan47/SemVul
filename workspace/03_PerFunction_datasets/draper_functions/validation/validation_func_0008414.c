RemoveRegOperandsFromUseLists(MachineRegisterInfo &MRI) {
  for (MachineOperand &MO : operands())
    if (MO.isReg())
      MRI.removeRegOperandFromUseList(&MO);
}
