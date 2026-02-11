arm_expand_vec_perm_1 (rtx target, rtx op0, rtx op1, rtx sel)
{
  enum machine_mode vmode = GET_MODE (target);
  bool one_vector_p = rtx_equal_p (op0, op1);

  gcc_checking_assert (vmode == V8QImode || vmode == V16QImode);
  gcc_checking_assert (GET_MODE (op0) == vmode);
  gcc_checking_assert (GET_MODE (op1) == vmode);
  gcc_checking_assert (GET_MODE (sel) == vmode);
  gcc_checking_assert (TARGET_NEON);

  if (one_vector_p)
    {
      if (vmode == V8QImode)
	emit_insn (gen_neon_vtbl1v8qi (target, op0, sel));
      else
	emit_insn (gen_neon_vtbl1v16qi (target, op0, sel));
    }
  else
    {
      rtx pair;

      if (vmode == V8QImode)
	{
	  pair = gen_reg_rtx (V16QImode);
	  emit_insn (gen_neon_vcombinev8qi (pair, op0, op1));
	  pair = gen_lowpart (TImode, pair);
	  emit_insn (gen_neon_vtbl2v8qi (target, pair, sel));
	}
      else
	{
	  pair = gen_reg_rtx (OImode);
	  emit_insn (gen_neon_vcombinev16qi (pair, op0, op1));
	  emit_insn (gen_neon_vtbl2v16qi (target, pair, sel));
	}
    }
}
