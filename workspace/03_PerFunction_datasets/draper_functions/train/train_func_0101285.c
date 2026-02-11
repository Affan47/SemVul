computePSetLimit(unsigned Idx) const {
  const TargetRegisterClass *RC = nullptr;
  unsigned NumRCUnits = 0;
  for (TargetRegisterInfo::regclass_iterator
         RI = TRI->regclass_begin(), RE = TRI->regclass_end(); RI != RE; ++RI) {
    const int *PSetID = TRI->getRegClassPressureSets(*RI);
    for (; *PSetID != -1; ++PSetID) {
      if ((unsigned)*PSetID == Idx)
        break;
    }
    if (*PSetID == -1)
      continue;


    unsigned NUnits = TRI->getRegClassWeight(*RI).WeightLimit;
    if (!RC || NUnits > NumRCUnits) {
      RC = *RI;
      NumRCUnits = NUnits;
    }
  }
  compute(RC);
  unsigned NReserved = RC->getNumRegs() - getNumAllocatableRegs(RC);
  return TRI->getRegPressureSetLimit(*MF, Idx) -
         TRI->getRegClassWeight(RC).RegWeight * NReserved;
}
