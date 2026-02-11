can_simplify_addr (rtx addr)
{
  rtx reg;

  if (CONSTANT_ADDRESS_P (addr))
    return false;

  if (GET_CODE (addr) == PLUS)
    reg = XEXP (addr, 0);
  else
    reg = addr;

  return (!REG_P (reg)
	  || (REGNO (reg) != FRAME_POINTER_REGNUM
	      && REGNO (reg) != HARD_FRAME_POINTER_REGNUM
	      && REGNO (reg) != ARG_POINTER_REGNUM));
}
