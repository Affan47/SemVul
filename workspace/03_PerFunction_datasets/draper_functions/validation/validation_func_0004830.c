simplify_subreg_regno (unsigned int xregno, enum machine_mode xmode,
		       unsigned int offset, enum machine_mode ymode)
{
  struct subreg_info info;
  unsigned int yregno;

#ifdef CANNOT_CHANGE_MODE_CLASS

  if (GET_MODE_CLASS (xmode) != MODE_COMPLEX_INT
      && GET_MODE_CLASS (xmode) != MODE_COMPLEX_FLOAT
      && REG_CANNOT_CHANGE_MODE_P (xregno, xmode, ymode)

      && ! lra_in_progress)
    return -1;
#endif


  if ((!reload_completed || frame_pointer_needed)
      && xregno == FRAME_POINTER_REGNUM)
    return -1;

  if (FRAME_POINTER_REGNUM != ARG_POINTER_REGNUM
      && xregno == ARG_POINTER_REGNUM)
    return -1;

  if (xregno == STACK_POINTER_REGNUM


      && ! lra_in_progress)
    return -1;


  subreg_get_info (xregno, xmode, offset, ymode, &info);
  if (!info.representable_p)
    return -1;


  yregno = xregno + info.offset;
  if (!HARD_REGISTER_NUM_P (yregno))
    return -1;


  if (!HARD_REGNO_MODE_OK (yregno, ymode)
      && HARD_REGNO_MODE_OK (xregno, xmode))
    return -1;

  return (int) yregno;
}
