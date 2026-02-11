getRegPressureLimit(const TargetRegisterClass *RC,
                                                  MachineFunction &MF) const {
  const AArch64FrameLowering *TFI = getFrameLowering(MF);

  switch (RC->getID()) {
  default:
    return 0;
  case AArch64::GPR32RegClassID:
  case AArch64::GPR32spRegClassID:
  case AArch64::GPR32allRegClassID:
  case AArch64::GPR64spRegClassID:
  case AArch64::GPR64allRegClassID:
  case AArch64::GPR64RegClassID:
  case AArch64::GPR32commonRegClassID:
  case AArch64::GPR64commonRegClassID:
    return 32 - 1
              - (TFI->hasFP(MF) || TT.isOSDarwin())
              - MF.getSubtarget<AArch64Subtarget>()
                    .isX18Reserved()
              - hasBasePointer(MF);
  case AArch64::FPR8RegClassID:
  case AArch64::FPR16RegClassID:
  case AArch64::FPR32RegClassID:
  case AArch64::FPR64RegClassID:
  case AArch64::FPR128RegClassID:
    return 32;

  case AArch64::DDRegClassID:
  case AArch64::DDDRegClassID:
  case AArch64::DDDDRegClassID:
  case AArch64::QQRegClassID:
  case AArch64::QQQRegClassID:
  case AArch64::QQQQRegClassID:
    return 32;

  case AArch64::FPR128_loRegClassID:
    return 16;
  }
}
