BinomialCoefficient(const SCEV *It, unsigned K,
                                       ScalarEvolution &SE,
                                       Type *ResultTy) {

  if (K == 1)
    return SE.getTruncateOrZeroExtend(It, ResultTy);


  if (K > 1000)
    return SE.getCouldNotCompute();

  unsigned W = SE.getTypeSizeInBits(ResultTy);


  APInt OddFactorial(W, 1);
  unsigned T = 1;
  for (unsigned i = 3; i <= K; ++i) {
    APInt Mult(W, i);
    unsigned TwoFactors = Mult.countTrailingZeros();
    T += TwoFactors;
    Mult = Mult.lshr(TwoFactors);
    OddFactorial *= Mult;
  }


  unsigned CalculationBits = W + T;


  APInt DivFactor = APInt(CalculationBits, 1).shl(T);


  APInt Mod = APInt::getSignedMinValue(W+1);
  APInt MultiplyFactor = OddFactorial.zext(W+1);
  MultiplyFactor = MultiplyFactor.multiplicativeInverse(Mod);
  MultiplyFactor = MultiplyFactor.trunc(W);


  IntegerType *CalculationTy = IntegerType::get(SE.getContext(),
                                                      CalculationBits);
  const SCEV *Dividend = SE.getTruncateOrZeroExtend(It, CalculationTy);
  for (unsigned i = 1; i != K; ++i) {
    const SCEV *S = SE.getMinusSCEV(It, SE.getConstant(It->getType(), i));
    Dividend = SE.getMulExpr(Dividend,
                             SE.getTruncateOrZeroExtend(S, CalculationTy));
  }


  const SCEV *DivResult = SE.getUDivExpr(Dividend, SE.getConstant(DivFactor));


  return SE.getMulExpr(SE.getConstant(MultiplyFactor),
                       SE.getTruncateOrZeroExtend(DivResult, ResultTy));
}
