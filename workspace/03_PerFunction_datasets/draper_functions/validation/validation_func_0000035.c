gen_split_2172 (rtx curr_insn ATTRIBUTE_UNUSED, rtx *operands)
{
  rtx operand0;
  rtx operand1;
  rtx operand2;
  rtx operand3;
  rtx _val = 0;
  start_sequence ();
#line 6733 "../../src/gcc/config/arm/arm.md"

  operands[2] = gen_lowpart (SImode, operands[0]);
  operands[3] = gen_lowpart (SImode, operands[1]);
  if (operands[2] == 0 || operands[3] == 0)
    FAIL;

  operand0 = operands[0];
  (void) operand0;
  operand1 = operands[1];
  (void) operand1;
  operand2 = operands[2];
  (void) operand2;
  operand3 = operands[3];
  (void) operand3;
  emit_insn (gen_rtx_SET (VOIDmode,
	operand2,
	operand3));
  _val = get_insns ();
  end_sequence ();
  return _val;
}
