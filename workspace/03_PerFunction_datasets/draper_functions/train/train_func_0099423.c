NegateValue(Value *V, Instruction *BI) {
  if (Constant *C = dyn_cast<Constant>(V)) {
    if (C->getType()->isFPOrFPVectorTy()) {
      return ConstantExpr::getFNeg(C);
    }
    return ConstantExpr::getNeg(C);
  }


  if (BinaryOperator *I =
          isReassociableOp(V, Instruction::Add, Instruction::FAdd)) {

    I->setOperand(0, NegateValue(I->getOperand(0), BI));
    I->setOperand(1, NegateValue(I->getOperand(1), BI));
    if (I->getOpcode() == Instruction::Add) {
      I->setHasNoUnsignedWrap(false);
      I->setHasNoSignedWrap(false);
    }


    I->moveBefore(BI);
    I->setName(I->getName()+".neg");
    return I;
  }


  for (User *U : V->users()) {
    if (!BinaryOperator::isNeg(U) && !BinaryOperator::isFNeg(U))
      continue;


    BinaryOperator *TheNeg = cast<BinaryOperator>(U);


    if (TheNeg->getParent()->getParent() != BI->getParent()->getParent())
      continue;

    BasicBlock::iterator InsertPt;
    if (Instruction *InstInput = dyn_cast<Instruction>(V)) {
      if (InvokeInst *II = dyn_cast<InvokeInst>(InstInput)) {
        InsertPt = II->getNormalDest()->begin();
      } else if (auto *CPI = dyn_cast<CatchPadInst>(InstInput)) {
        InsertPt = CPI->getNormalDest()->begin();
      } else {
        InsertPt = ++InstInput->getIterator();
      }
      while (isa<PHINode>(InsertPt)) ++InsertPt;
    } else {
      InsertPt = TheNeg->getParent()->getParent()->getEntryBlock().begin();
    }
    TheNeg->moveBefore(&*InsertPt);
    if (TheNeg->getOpcode() == Instruction::Sub) {
      TheNeg->setHasNoUnsignedWrap(false);
      TheNeg->setHasNoSignedWrap(false);
    } else {
      TheNeg->andIRFlags(BI);
    }
    return TheNeg;
  }


  return CreateNeg(V, V->getName() + ".neg", BI, BI);
}
