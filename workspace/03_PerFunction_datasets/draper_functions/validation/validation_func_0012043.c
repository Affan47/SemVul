gen_insv (rtx operand0,
	rtx operand1,
	rtx operand2,
	rtx operand3)
{
  rtx _val = 0;
  start_sequence ();
  {
    rtx operands[4];
    operands[0] = operand0;
    operands[1] = operand1;
    operands[2] = operand2;
    operands[3] = operand3;
#line 3389 "../../src/gcc/config/rs6000/rs6000.md"

{


  if (GET_CODE (operands[0]) == SUBREG
      && (GET_MODE_SIZE (GET_MODE (SUBREG_REG (operands[0]))) < UNITS_PER_WORD
	  || ((TARGET_E500_DOUBLE || TARGET_SPE)
	      && invalid_e500_subreg (operands[0], GET_MODE (operands[0])))))
    FAIL;

  if (TARGET_POWERPC64 && GET_MODE (operands[0]) == DImode)
    emit_insn (gen_insvdi_internal (operands[0], operands[1], operands[2],
				    operands[3]));
  else
    emit_insn (gen_insvsi_internal (operands[0], operands[1], operands[2],
				    operands[3]));
  DONE;
}
    operand0 = operands[0];
    (void) operand0;
    operand1 = operands[1];
    (void) operand1;
    operand2 = operands[2];
    (void) operand2;
    operand3 = operands[3];
    (void) operand3;
  }
  emit_insn (gen_rtx_SET (VOIDmode,
	gen_rtx_ZERO_EXTRACT (VOIDmode,
	operand0,
	operand1,
	operand2),
	operand3));
  _val = get_insns ();
  end_sequence ();
  return _val;
}
