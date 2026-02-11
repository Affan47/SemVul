InvalidateKill(unsigned Reg,
                           const TargetRegisterInfo* TRI,
                           BitVector &RegKills,
                           std::vector<MachineOperand*> &KillOps) {
  if (RegKills[Reg]) {
    KillOps[Reg]->setIsKill(false);

    unsigned KReg = KillOps[Reg]->getReg();
    KillOps[KReg] = NULL;
    RegKills.reset(KReg);
    for (const unsigned *SR = TRI->getSubRegisters(KReg); *SR; ++SR) {
      if (RegKills[*SR]) {
        KillOps[*SR]->setIsKill(false);
        KillOps[*SR] = NULL;
        RegKills.reset(*SR);
      }
    }
  }
}
