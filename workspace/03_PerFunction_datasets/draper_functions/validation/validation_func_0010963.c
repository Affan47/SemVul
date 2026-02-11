rewriteImplies(const Expr& e) {
  Proof pf;
  if(CHECK_PROOFS)
    CHECK_SOUND(e.isImpl(), "rewriteImplies precondition violated");
  if(withProof()) {
    pf = newPf("rewrite_implies", e[0], e[1]);
  }
  return newRWTheorem(e, !e[0] || e[1], Assumptions::emptyAssump(), pf);
}
