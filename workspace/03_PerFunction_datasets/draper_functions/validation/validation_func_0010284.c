intEqIrrational(const Expr& expr, const Theorem& isIntx)
{
  if (CHECK_PROOFS) {
    CHECK_SOUND(expr.isEq() && isPow(expr[0]) &&
                expr[1].isRational() &&
                expr[1].getRational() != 0 &&
                isIntegerConst(expr[0][0]) &&
                expr[0][0].getRational() > 0 &&
                ratRoot(expr[1].getRational(), expr[0][0].getRational().getUnsigned()) == 0,
                "intEqIrrational invariant violated"+expr.toString());
    CHECK_SOUND(isIntPred(isIntx.getExpr()) && isIntx.getExpr()[0] == expr[0][1],
		"ArithTheoremProducer3::intEqIrrational:\n "
		"wrong integrality constraint:\n expr = "
		+expr.toString()+"\n isIntx = "
		+isIntx.getExpr().toString());
  }
  const Assumptions& assump(isIntx.getAssumptionsRef());
  Proof pf;
  if (withProof()) {
    pf = newPf("int_eq_irr", expr, isIntx.getProof());
  }
  return newRWTheorem(expr, d_em->falseExpr(), assump, pf);
}
