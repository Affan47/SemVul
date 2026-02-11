CCAssignFnForCall(CallingConv::ID CC, bool Return) {
  switch (CC) {
  default:
    llvm_unreachable("Unsupported calling convention");
  case CallingConv::Fast:

    (void)RetFastCC_ARM_APCS;
    (void)FastCC_ARM_APCS;

  case CallingConv::C:

    if (Subtarget->isAAPCS_ABI()) {
      if (Subtarget->hasVFP2() &&
          FloatABIType == FloatABI::Hard)
        return (Return ? RetCC_ARM_AAPCS_VFP: CC_ARM_AAPCS_VFP);
      else
        return (Return ? RetCC_ARM_AAPCS: CC_ARM_AAPCS);
    } else
        return (Return ? RetCC_ARM_APCS: CC_ARM_APCS);
  case CallingConv::ARM_AAPCS_VFP:
    return (Return ? RetCC_ARM_AAPCS_VFP: CC_ARM_AAPCS_VFP);
  case CallingConv::ARM_AAPCS:
    return (Return ? RetCC_ARM_AAPCS: CC_ARM_AAPCS);
  case CallingConv::ARM_APCS:
    return (Return ? RetCC_ARM_APCS: CC_ARM_APCS);
  }
}
