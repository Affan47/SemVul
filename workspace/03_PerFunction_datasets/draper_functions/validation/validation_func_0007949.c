mergeLabels(const Theorem& thm, const Expr& e,
                                 unsigned position, bool positive)
{
  DebugAssert(e.hasFind() && findExpr(e) == e,
              "datatype: mergeLabels2: Expected find(e)=e");
  DebugAssert(d_labels.find(e) != d_labels.end(),
              "mergeLabels2: expr is not labeled");
  Unsigned u = d_labels[e].get().get();
  Unsigned uNew = (Unsigned)1 << position;
  if (positive) {
    uNew = u & uNew;
    if (u == uNew) return;
  } else if ((u & uNew) != 0) uNew = u - uNew;
  else return;
  d_facts.push_back(thm);
  d_labels[e].get().set(uNew);
  if (uNew == 0)
    setInconsistent(d_rules->dummyTheorem(d_facts, falseExpr()));
  else if (((uNew - 1) & uNew) == 0) {
    instantiate(e, uNew);
  }
}
