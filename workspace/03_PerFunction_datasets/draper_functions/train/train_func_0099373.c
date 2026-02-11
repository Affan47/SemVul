copyKillDeadInfo(const MachineInstr *MI) {
  for (unsigned i = 0, e = MI->getNumOperands(); i != e; ++i) {
    const MachineOperand &MO = MI->getOperand(i);
    if (!MO.isReg() || (!MO.isKill() && !MO.isDead()))
      continue;
    for (unsigned j = 0, ee = getNumOperands(); j != ee; ++j) {
      MachineOperand &MOp = getOperand(j);
      if (!MOp.isIdenticalTo(MO))
        continue;
      if (MO.isKill())
        MOp.setIsKill();
      else
        MOp.setIsDead();
      break;
    }
  }
}
