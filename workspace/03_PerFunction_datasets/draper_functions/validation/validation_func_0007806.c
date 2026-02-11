processInstruction(MachineInstr &MI) {

  if (Instrs.count(MI.getOpcode())) {
    const RndModeDesc &Desc = Instrs[MI.getOpcode()];

    MachineOperand &Op = MI.getOperand(Desc.first);

    if (Op.getImm() == PTXRoundingMode::RndDefault) {
      Op.setImm(Desc.second);
    }
  }
}
