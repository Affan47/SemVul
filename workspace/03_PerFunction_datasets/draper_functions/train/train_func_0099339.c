SimplifyWithOpReplaced(Value *V, Value *Op, Value *RepOp,
                                     const TargetData *TD) {

  if (V == Op)
    return RepOp;

  Instruction *I = dyn_cast<Instruction>(V);
  if (!I)
    return 0;


  if (BinaryOperator *B = dyn_cast<BinaryOperator>(I)) {
    if (B->getOperand(0) == Op)
      return SimplifyBinOp(B->getOpcode(), RepOp, B->getOperand(1), TD);
    if (B->getOperand(1) == Op)
      return SimplifyBinOp(B->getOpcode(), B->getOperand(0), RepOp, TD);
  }


  if (CmpInst *C = dyn_cast<CmpInst>(I)) {
    if (C->getOperand(0) == Op)
      return SimplifyCmpInst(C->getPredicate(), RepOp, C->getOperand(1), TD);
    if (C->getOperand(1) == Op)
      return SimplifyCmpInst(C->getPredicate(), C->getOperand(0), RepOp, TD);
  }


  if (Constant *CRepOp = dyn_cast<Constant>(RepOp)) {

    SmallVector<Constant*, 8> ConstOps;
    for (unsigned i = 0, e = I->getNumOperands(); i != e; ++i) {
      if (I->getOperand(i) == Op)
        ConstOps.push_back(CRepOp);
      else if (Constant *COp = dyn_cast<Constant>(I->getOperand(i)))
        ConstOps.push_back(COp);
      else
        break;
    }


    if (ConstOps.size() == I->getNumOperands()) {
      if (LoadInst *LI = dyn_cast<LoadInst>(I))
        if (!LI->isVolatile())
          return ConstantFoldLoadFromConstPtr(ConstOps[0], TD);

      return ConstantFoldInstOperands(I->getOpcode(), I->getType(),
                                      ConstOps, TD);
    }
  }

  return 0;
}
