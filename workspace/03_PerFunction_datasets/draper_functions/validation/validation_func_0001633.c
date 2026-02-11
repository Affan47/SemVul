getFeasibleSuccessors(TerminatorInst &TI,
                                         SmallVectorImpl<bool> &Succs,
                                         bool AggressiveUndef) {
  Succs.resize(TI.getNumSuccessors());
  if (TI.getNumSuccessors() == 0) return;

  if (BranchInst *BI = dyn_cast<BranchInst>(&TI)) {
    if (BI->isUnconditional()) {
      Succs[0] = true;
      return;
    }

    LatticeVal BCValue;
    if (AggressiveUndef)
      BCValue = getOrInitValueState(BI->getCondition());
    else
      BCValue = getLatticeState(BI->getCondition());

    if (BCValue == LatticeFunc->getOverdefinedVal() ||
        BCValue == LatticeFunc->getUntrackedVal()) {

      Succs[0] = Succs[1] = true;
      return;
    }


    if (BCValue == LatticeFunc->getUndefVal())
      return;

    Constant *C = LatticeFunc->GetConstant(BCValue, BI->getCondition(), *this);
    if (!C || !isa<ConstantInt>(C)) {

      Succs[0] = Succs[1] = true;
      return;
    }


    Succs[C->isNullValue()] = true;
    return;
  }

  if (isa<InvokeInst>(TI)) {


    Succs[0] = Succs[1] = true;
    return;
  }

  if (isa<IndirectBrInst>(TI)) {
    Succs.assign(Succs.size(), true);
    return;
  }

  SwitchInst &SI = cast<SwitchInst>(TI);
  LatticeVal SCValue;
  if (AggressiveUndef)
    SCValue = getOrInitValueState(SI.getCondition());
  else
    SCValue = getLatticeState(SI.getCondition());

  if (SCValue == LatticeFunc->getOverdefinedVal() ||
      SCValue == LatticeFunc->getUntrackedVal()) {

    Succs.assign(TI.getNumSuccessors(), true);
    return;
  }


  if (SCValue == LatticeFunc->getUndefVal())
    return;

  Constant *C = LatticeFunc->GetConstant(SCValue, SI.getCondition(), *this);
  if (!C || !isa<ConstantInt>(C)) {

    Succs.assign(TI.getNumSuccessors(), true);
    return;
  }
  SwitchInst::CaseIt Case = SI.findCaseValue(cast<ConstantInt>(C));
  Succs[Case.getSuccessorIndex()] = true;
}
