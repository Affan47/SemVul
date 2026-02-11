ExtractEquivalentCondition(Value *V, CmpInst::Predicate Pred,
                                         Value *LHS, Value *RHS) {
  SelectInst *SI = dyn_cast<SelectInst>(V);
  if (!SI)
    return nullptr;
  CmpInst *Cmp = dyn_cast<CmpInst>(SI->getCondition());
  if (!Cmp)
    return nullptr;
  Value *CmpLHS = Cmp->getOperand(0), *CmpRHS = Cmp->getOperand(1);
  if (Pred == Cmp->getPredicate() && LHS == CmpLHS && RHS == CmpRHS)
    return Cmp;
  if (Pred == CmpInst::getSwappedPredicate(Cmp->getPredicate()) &&
      LHS == CmpRHS && RHS == CmpLHS)
    return Cmp;
  return nullptr;
}
