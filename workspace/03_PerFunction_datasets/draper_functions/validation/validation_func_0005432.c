createNodeForGEP(GEPOperator *GEP) {


  bool isInBounds = GEP->isInBounds();

  Type *IntPtrTy = getEffectiveSCEVType(GEP->getType());
  Value *Base = GEP->getOperand(0);

  if (!cast<PointerType>(Base->getType())->getElementType()->isSized())
    return getUnknown(GEP);
  const SCEV *TotalOffset = getConstant(IntPtrTy, 0);
  gep_type_iterator GTI = gep_type_begin(GEP);
  for (GetElementPtrInst::op_iterator I = llvm::next(GEP->op_begin()),
                                      E = GEP->op_end();
       I != E; ++I) {
    Value *Index = *I;

    if (StructType *STy = dyn_cast<StructType>(*GTI++)) {

      unsigned FieldNo = cast<ConstantInt>(Index)->getZExtValue();
      const SCEV *FieldOffset = getOffsetOfExpr(STy, FieldNo);


      TotalOffset = getAddExpr(TotalOffset, FieldOffset);
    } else {

      const SCEV *ElementSize = getSizeOfExpr(*GTI);
      const SCEV *IndexS = getSCEV(Index);

      IndexS = getTruncateOrSignExtend(IndexS, IntPtrTy);


      const SCEV *LocalOffset = getMulExpr(IndexS, ElementSize,
                                           isInBounds ? SCEV::FlagNSW :
                                           SCEV::FlagAnyWrap);


      TotalOffset = getAddExpr(TotalOffset, LocalOffset);
    }
  }


  const SCEV *BaseS = getSCEV(Base);


  return getAddExpr(BaseS, TotalOffset,
                    isInBounds ? SCEV::FlagNSW : SCEV::FlagAnyWrap);
}
