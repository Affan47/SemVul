getCombinedIndex(const MachineInstr *CPEMI) {
  if (CPEMI->getOperand(1).isCPI())
    return CPEMI->getOperand(1).getIndex();

  return JumpTableEntryIndices[CPEMI->getOperand(1).getIndex()];
}
