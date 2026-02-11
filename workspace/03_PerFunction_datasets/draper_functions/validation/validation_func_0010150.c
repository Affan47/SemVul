isLowerSubst(const double inf,
				      const double aj,
				      const double xlp,
				      const double LB,
				      const double UB) const
{
  if (CRITERION_ == 1) {

    return xlp - LB < UB - xlp;
  }
  else {
    if (UB == inf || xlp == LB)
      return true;
    if (LB == -inf || xlp == UB)
      return false;
    if (CRITERION_ == 2)

      return aj < 0;
    else

      return aj > 0;
  }
}
