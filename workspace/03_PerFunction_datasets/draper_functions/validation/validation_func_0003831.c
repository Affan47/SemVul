isNullValue() const {

  if (const ConstantInt *CI = dyn_cast<ConstantInt>(this))
    return CI->isZero();


  if (const ConstantFP *CFP = dyn_cast<ConstantFP>(this))
    return CFP->isZero() && !CFP->isNegative();


  return isa<ConstantAggregateZero>(this) || isa<ConstantPointerNull>(this);
}
