EmitPreheaderBranchOnCondition(Value *LIC, Constant *Val,
                                                  BasicBlock *TrueDest,
                                                  BasicBlock *FalseDest,
                                                  Instruction *InsertPt) {


  Value *BranchVal = LIC;
  if (!isa<ConstantInt>(Val) ||
      Val->getType() != Type::getInt1Ty(LIC->getContext()))
    BranchVal = new ICmpInst(InsertPt, ICmpInst::ICMP_EQ, LIC, Val);
  else if (Val != ConstantInt::getTrue(Val->getContext()))

    std::swap(TrueDest, FalseDest);


  BranchInst *BI = BranchInst::Create(TrueDest, FalseDest, BranchVal, InsertPt);


  SplitCriticalEdge(BI, 0, this);
  SplitCriticalEdge(BI, 1, this);
}
