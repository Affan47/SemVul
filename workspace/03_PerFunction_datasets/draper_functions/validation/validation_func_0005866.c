tryReassociatedBinaryOp(const SCEV *LHSExpr,
                                                      Value *RHS,
                                                      BinaryOperator *I) {


  auto *LHS = findClosestMatchingDominator(LHSExpr, I);
  if (LHS == nullptr)
    return nullptr;

  Instruction *NewI = nullptr;
  switch (I->getOpcode()) {
  case Instruction::Add:
    NewI = BinaryOperator::CreateAdd(LHS, RHS, "", I);
    break;
  case Instruction::Mul:
    NewI = BinaryOperator::CreateMul(LHS, RHS, "", I);
    break;
  default:
    llvm_unreachable("Unexpected instruction.");
  }
  NewI->takeName(I);
  return NewI;
}
