PredicateInstruction(MachineInstr *MI,
                                    ArrayRef<MachineOperand> Pred) const {
  int PIdx = MI->findFirstPredOperandIdx();

  if (MI->getOpcode() == AMDGPU::CF_ALU) {
    MI->getOperand(8).setImm(0);
    return true;
  }

  if (MI->getOpcode() == AMDGPU::DOT_4) {
    MI->getOperand(getOperandIdx(*MI, AMDGPU::OpName::pred_sel_X))
        .setReg(Pred[2].getReg());
    MI->getOperand(getOperandIdx(*MI, AMDGPU::OpName::pred_sel_Y))
        .setReg(Pred[2].getReg());
    MI->getOperand(getOperandIdx(*MI, AMDGPU::OpName::pred_sel_Z))
        .setReg(Pred[2].getReg());
    MI->getOperand(getOperandIdx(*MI, AMDGPU::OpName::pred_sel_W))
        .setReg(Pred[2].getReg());
    MachineInstrBuilder MIB(*MI->getParent()->getParent(), MI);
    MIB.addReg(AMDGPU::PREDICATE_BIT, RegState::Implicit);
    return true;
  }

  if (PIdx != -1) {
    MachineOperand &PMO = MI->getOperand(PIdx);
    PMO.setReg(Pred[2].getReg());
    MachineInstrBuilder MIB(*MI->getParent()->getParent(), MI);
    MIB.addReg(AMDGPU::PREDICATE_BIT, RegState::Implicit);
    return true;
  }

  return false;
}
