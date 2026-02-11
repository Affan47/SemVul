get_subtarget (x)
     rtx x;
{
  return ((x == 0

	   || GET_CODE (x) != REG

	   || RTX_UNCHANGING_P (x)

	   || REGNO (x) < FIRST_PSEUDO_REGISTER


	   || preserve_subexpressions_p ())
	  ? 0 : x);
}
