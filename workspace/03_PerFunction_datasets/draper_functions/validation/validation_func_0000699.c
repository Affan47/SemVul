isInvariantIn(Value *Val, Loop *L) {
  if (isa<Constant>(Val) || isa<Argument>(Val))
    return true;
  Instruction *In = dyn_cast<Instruction>(Val);
  if (!In)
    return false;
  BasicBlock *HdrB = L->getHeader(), *DefB = In->getParent();
  return DT->properlyDominates(DefB, HdrB);
}
