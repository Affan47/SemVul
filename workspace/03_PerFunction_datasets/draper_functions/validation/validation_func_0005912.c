p1d_varsel (splotd * sp, gint jvar, gint * jprev, gint toggle, gint mouse)
{
  gboolean redraw = true;
  displayd *display = (displayd *) sp->displayptr;
  gint orientation = display->p1d_orientation;
  gboolean allow = true;

  if (GGOBI_IS_EXTENDED_DISPLAY (display)) {
    allow = GGOBI_EXTENDED_DISPLAY_GET_CLASS (display)->allow_reorientation;
  }


  if (allow && mouse > 0)
    display->p1d_orientation = (mouse == 1) ? HORIZONTAL : VERTICAL;

  redraw = (orientation != display->p1d_orientation) || (jvar != sp->p1dvar);

  *jprev = sp->p1dvar;
  sp->p1dvar = jvar;

  if (orientation != display->p1d_orientation)
    scatterplot_show_rulers (display, P1PLOT);

  return redraw;
}
