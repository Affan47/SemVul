ra_setup(ASMState *as)
{
  Reg r;

  as->freeset = RSET_INIT;
  as->modset = RSET_EMPTY;
  as->weakset = RSET_EMPTY;
  as->phiset = RSET_EMPTY;
  memset(as->phireg, 0, sizeof(as->phireg));
  for (r = RID_MIN_GPR; r < RID_MAX; r++)
    as->cost[r] = REGCOST(~0u, 0u);
}
