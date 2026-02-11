approx_reg_cost (rtx x)
{
  int cost = 0;

  if (for_each_rtx (&x, approx_reg_cost_1, (void *) &cost))
    return MAX_COST;

  return cost;
}
