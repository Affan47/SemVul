get_regset_from_pool (void)
{
  regset rs;

  if (regset_pool.n != 0)
    rs = regset_pool.v[--regset_pool.n];
  else

    {
      rs = ALLOC_REG_SET (&reg_obstack);

      if (regset_pool.nn == regset_pool.ss)
	regset_pool.vv = XRESIZEVEC (regset, regset_pool.vv,
                                     (regset_pool.ss = 2 * regset_pool.ss + 1));
      regset_pool.vv[regset_pool.nn++] = rs;
    }

  regset_pool.diff++;

  return rs;
}
