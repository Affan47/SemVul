needsUnimp(MachineBasicBlock::iterator I, unsigned &StructSize)
{
  if (!I->isCall())
    return false;

  unsigned structSizeOpNum = 0;
  switch (I->getOpcode()) {
  default: llvm_unreachable("Unknown call opcode.");
  case SP::CALL: structSizeOpNum = 1; break;
  case SP::CALLrr:
  case SP::CALLri: structSizeOpNum = 2; break;
  case SP::TLS_CALL: return false;
  }

  const MachineOperand &MO = I->getOperand(structSizeOpNum);
  if (!MO.isImm())
    return false;
  StructSize = MO.getImm();
  return true;
}
