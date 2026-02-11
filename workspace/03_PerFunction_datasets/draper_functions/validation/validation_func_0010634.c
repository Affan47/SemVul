iv_subreg (struct rtx_iv *iv, enum machine_mode mode)
{

  if (iv->step == const0_rtx
      && !iv->first_special)
    {
      rtx val = get_iv_value (iv, const0_rtx);
      val = lowpart_subreg (mode, val, iv->extend_mode);

      iv->base = val;
      iv->extend = UNKNOWN;
      iv->mode = iv->extend_mode = mode;
      iv->delta = const0_rtx;
      iv->mult = const1_rtx;
      return true;
    }

  if (iv->extend_mode == mode)
    return true;

  if (GET_MODE_BITSIZE (mode) > GET_MODE_BITSIZE (iv->mode))
    return false;

  iv->extend = UNKNOWN;
  iv->mode = mode;

  iv->base = simplify_gen_binary (PLUS, iv->extend_mode, iv->delta,
				  simplify_gen_binary (MULT, iv->extend_mode,
						       iv->base, iv->mult));
  iv->step = simplify_gen_binary (MULT, iv->extend_mode, iv->step, iv->mult);
  iv->mult = const1_rtx;
  iv->delta = const0_rtx;
  iv->first_special = false;

  return true;
}
