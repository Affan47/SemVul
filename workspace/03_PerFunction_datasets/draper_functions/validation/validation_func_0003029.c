rewriteIteCond(const Expr& e)
{
  if (CHECK_PROOFS)
    CHECK_SOUND(e.isITE() && e.arity()==3, "rewriteIteCond: " + e.toString());

  vector<Expr> oldTerms, newTerms;


  oldTerms.push_back(e[0]);
  newTerms.push_back(d_em->trueExpr());


  Expr e1(e[1].substExpr(oldTerms, newTerms));
  oldTerms[0] = e[0];
  newTerms[0] = d_em->falseExpr();
  Expr e2(e[2].substExpr(oldTerms, newTerms));

  Proof pf;
  if (withProof()) pf = newPf("rewrite_ite_cond", e);
  return newRWTheorem(e, e[0].iteExpr(e1, e2), Assumptions::emptyAssump(), pf);
}
