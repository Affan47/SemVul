compute_a_shift_cc (rtx insn ATTRIBUTE_UNUSED, rtx *operands)
{
  rtx shift = operands[3];
  enum machine_mode mode = GET_MODE (shift);
  enum rtx_code code = GET_CODE (shift);
  enum shift_type shift_type;
  enum shift_mode shift_mode;
  struct shift_info info;

  switch (mode)
    {
    case QImode:
      shift_mode = QIshift;
      break;
    case HImode:
      shift_mode = HIshift;
      break;
    case SImode:
      shift_mode = SIshift;
      break;
    default:
      abort ();
    }

  switch (code)
    {
    case ASHIFTRT:
      shift_type = SHIFT_ASHIFTRT;
      break;
    case LSHIFTRT:
      shift_type = SHIFT_LSHIFTRT;
      break;
    case ASHIFT:
      shift_type = SHIFT_ASHIFT;
      break;
    default:
      abort ();
    }

  if (GET_CODE (operands[2]) != CONST_INT)
    {


      abort ();
    }
  else
    {
      int n = INTVAL (operands[2]);


      if (n < 0)
	n = 0;


      else if ((unsigned int) n > GET_MODE_BITSIZE (mode))
	n = GET_MODE_BITSIZE (mode);

      get_shift_alg (shift_type, shift_mode, n, &info);

      switch (info.alg)
	{
	case SHIFT_SPECIAL:
	  if (info.remainder == 0)
	    return info.cc_special;


	case SHIFT_INLINE:
	  return info.cc_inline;

	case SHIFT_ROT_AND:

	  return CC_SET_ZNV;

	case SHIFT_LOOP:


	  if (info.shift2 != NULL)
	    {
	      if (n % 2)
		return info.cc_inline;
	    }
	  return CC_CLOBBER;

	default:
	  abort ();
	}
    }
}
