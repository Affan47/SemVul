VerifyLowRegs(MachineInstr *MI) {
  unsigned Opc = MI->getOpcode();
  bool isPCOk = (Opc == ARM::t2LDMIA_RET || Opc == ARM::t2LDMIA     ||
                 Opc == ARM::t2LDMDB     || Opc == ARM::t2LDMIA_UPD ||
                 Opc == ARM::t2LDMDB_UPD);
  bool isLROk = (Opc == ARM::t2STMIA_UPD || Opc == ARM::t2STMDB_UPD);
  bool isSPOk = isPCOk || isLROk;
  for (unsigned i = 0, e = MI->getNumOperands(); i != e; ++i) {
    const MachineOperand &MO = MI->getOperand(i);
    if (!MO.isReg() || MO.isImplicit())
      continue;
    unsigned Reg = MO.getReg();
    if (Reg == 0 || Reg == ARM::CPSR)
      continue;
    if (isPCOk && Reg == ARM::PC)
      continue;
    if (isLROk && Reg == ARM::LR)
      continue;
    if (Reg == ARM::SP) {
      if (isSPOk)
        continue;
      if (i == 1 && (Opc == ARM::t2LDRi12 || Opc == ARM::t2STRi12))

        continue;
    }
    if (!isARMLowRegister(Reg))
      return false;
  }
  return true;
}
