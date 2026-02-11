__roundf (float x)
{
  int32_t i0, j0;

  GET_FLOAT_WORD (i0, x);
  j0 = ((i0 >> 23) & 0xff) - 0x7f;
  if (j0 < 23)
    {
      if (j0 < 0)
	{
	  math_force_eval (huge + x);

	  i0 &= 0x80000000;
	  if (j0 == -1)
	    i0 |= 0x3f800000;
	}
      else
	{
	  u_int32_t i = 0x007fffff >> j0;
	  if ((i0 & i) == 0)

	    return x;
	  math_force_eval (huge + x);


	  i0 += 0x00400000 >> j0;
	  i0 &= ~i;
	}
    }
  else
    {
      if (j0 == 0x80)

	return x + x;
      else
	return x;
    }

  SET_FLOAT_WORD (x, i0);
  return x;
}
