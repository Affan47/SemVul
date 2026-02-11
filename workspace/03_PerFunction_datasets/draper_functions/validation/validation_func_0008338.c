isUsedOutsideOfDefiningBlock(const Instruction *I) {
  if (I->use_empty()) return false;
  if (isa<PHINode>(I)) return true;
  const BasicBlock *BB = I->getParent();
  for (const User *U : I->users())
    if (cast<Instruction>(U)->getParent() != BB || isa<PHINode>(U))
      return true;

  return false;
}
