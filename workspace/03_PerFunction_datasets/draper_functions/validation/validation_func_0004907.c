getEmergencySpillSlot(const TargetRegisterClass *RC) {
  std::map<const TargetRegisterClass*, int>::iterator I =
    EmergencySpillSlots.find(RC);
  if (I != EmergencySpillSlots.end())
    return I->second;
  int SS = MF->getFrameInfo()->CreateSpillStackObject(RC->getSize(),
                                                 RC->getAlignment());
  if (LowSpillSlot == NO_STACK_SLOT)
    LowSpillSlot = SS;
  if (HighSpillSlot == NO_STACK_SLOT || SS > HighSpillSlot)
    HighSpillSlot = SS;
  EmergencySpillSlots[RC] = SS;
  return SS;
}
