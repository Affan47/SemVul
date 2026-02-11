gen_sqrtv8sf2 (rtx operand0,
	rtx operand1)
{
  rtx _val = 0;
  start_sequence ();
  {
    rtx operands[2];
    operands[0] = operand0;
    operands[1] = operand1;
#line 887 "../../src/gcc/config/i386/sse.md"
{
  if (TARGET_SSE_MATH && TARGET_RECIP && !optimize_insn_for_size_p ()
      && flag_finite_math_only && !flag_trapping_math
      && flag_unsafe_math_optimizations)
    {
      ix86_emit_swsqrtsf (operands[0], operands[1], V8SFmode, 0);
      DONE;
    }
}
    operand0 = operands[0];
    (void) operand0;
    operand1 = operands[1];
    (void) operand1;
  }
  emit_insn (gen_rtx_SET (VOIDmode,
	operand0,
	gen_rtx_SQRT (V8SFmode,
	operand1)));
  _val = get_insns ();
  end_sequence ();
  return _val;
}
