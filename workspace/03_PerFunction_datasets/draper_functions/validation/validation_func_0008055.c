mergeAssumeBlockValueConstantRange(Value *Val,
                                                            LVILatticeVal &BBLV,
                                                            Instruction *BBI) {
  BBI = BBI ? BBI : dyn_cast<Instruction>(Val);
  if (!BBI)
    return;

  for (auto &AssumeVH : AC->assumptions()) {
    if (!AssumeVH)
      continue;
    auto *I = cast<CallInst>(AssumeVH);
    if (!isValidAssumeForContext(I, BBI, DT))
      continue;

    Value *C = I->getArgOperand(0);
    if (ICmpInst *ICI = dyn_cast<ICmpInst>(C)) {
      LVILatticeVal Result;
      if (getValueFromFromCondition(Val, ICI, Result)) {
        if (BBLV.isOverdefined())
          BBLV = Result;
        else
          BBLV.mergeIn(Result, DL);
      }
    }
  }
}
