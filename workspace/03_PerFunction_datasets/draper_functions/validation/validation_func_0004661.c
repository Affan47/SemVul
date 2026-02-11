grid_mpress(But *but, int butnum, int x, int y)  {
  int  newflags = but->flags, retval = BUTOUT_CAUGHT;
  Grid  *grid;

  if (butnum == 1)  {
    grid = but->iPacket;
    assert(MAGIC(grid));


    if (((but->win->env->keyModifiers & (ShiftMask | ControlMask)) == 0) &&
	grid->holdRequired && grid->b->holdEnabled &&
	(butWin_env(but_win(but))->eventTime - grid->b->holdStart <
	 CGBUTS_HOLDTIME))
      retval |= BUTOUT_ERR;
    else
      newflags |= BUT_PRESSED|BUT_LOCKED;
  } else
    retval |= BUTOUT_ERR;


  if (newflags != but->flags)
    but_newFlags(but, newflags);
  return(retval);
}
