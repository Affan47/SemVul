SimplifyShlInst(Value *Op0, Value *Op1, bool isNSW, bool isNUW,
                              const TargetData *TD, const DominatorTree *DT,
                              unsigned MaxRecurse) {
  if (Value *V = SimplifyShift(Instruction::Shl, Op0, Op1, TD, DT, MaxRecurse))
    return V;


  if (match(Op0, m_Undef()))
    return Constant::getNullValue(Op0->getType());


  Value *X;
  if (match(Op0, m_Shr(m_Value(X), m_Specific(Op1))) &&
      cast<PossiblyExactOperator>(Op0)->isExact())
    return X;
  return 0;
}
