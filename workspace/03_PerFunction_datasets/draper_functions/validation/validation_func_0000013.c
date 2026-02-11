plus_minus_operand_p (const_rtx x)
{
  return GET_CODE (x) == PLUS
         || GET_CODE (x) == MINUS
	 || (GET_CODE (x) == CONST
	     && GET_CODE (XEXP (x, 0)) == PLUS
	     && CONSTANT_P (XEXP (XEXP (x, 0), 0))
	     && CONSTANT_P (XEXP (XEXP (x, 0), 1)));
}
