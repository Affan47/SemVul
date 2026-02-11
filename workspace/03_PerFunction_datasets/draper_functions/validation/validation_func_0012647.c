ira_adjust_equiv_reg_cost (unsigned regno, int cost)
{
  if (cost == 0)
    regno_equiv_gains[regno] = 0;
  else
    regno_equiv_gains[regno] += cost;
}
