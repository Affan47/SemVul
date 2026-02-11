hasFP(const MachineFunction &MF) const {
  const MachineFrameInfo *MFI = MF.getFrameInfo();
  const MachineModuleInfo &MMI = MF.getMMI();
  const TargetRegisterInfo *RI = TM.getRegisterInfo();

  return (DisableFramePointerElim(MF) ||
          RI->needsStackRealignment(MF) ||
          MFI->hasVarSizedObjects() ||
          MFI->isFrameAddressTaken() ||
          MF.getInfo<X86MachineFunctionInfo>()->getForceFramePointer() ||
          MMI.callsUnwindInit());
}
