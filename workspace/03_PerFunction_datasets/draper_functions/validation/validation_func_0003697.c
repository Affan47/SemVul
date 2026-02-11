splat_input_operand_1 (rtx op, enum machine_mode mode ATTRIBUTE_UNUSED)
#line 1144 "../../src/gcc/config/rs6000/predicates.md"
{
  if (MEM_P (op))
    {
      if (! volatile_ok && MEM_VOLATILE_P (op))
	return 0;
      if (mode == DFmode)
	mode = V2DFmode;
      else if (mode == DImode)
	mode = V2DImode;
      else
	gcc_unreachable ();
      return memory_address_addr_space_p (mode, XEXP (op, 0),
					  MEM_ADDR_SPACE (op));
    }
  return input_operand (op, mode);
}
