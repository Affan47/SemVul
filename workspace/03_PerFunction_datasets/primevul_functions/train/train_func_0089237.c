scroll_rect(int topline, int botline, int lines)
{

  int y0, y1, y2, e0, e1;
  if (lines < 0) {


    if (topline - lines > term.marg_bot + 1)
      lines = topline - term.marg_bot - 1;
    y0 = topline;
    y1 = botline + lines;
    y2 = topline - lines;
    e0 = y0;
    e1 = y0 - lines - 1;
  }
  else {


    if (topline + lines > term.marg_bot + 1)
      lines = term.marg_bot + 1 - topline;
    y0 = topline + lines;
    y1 = botline;
    y2 = topline;
    e0 = y1 - lines + 1;
    e1 = y1;
  }
  y0++; y1++; y2++; e0++; e1++;
  int xl = term.marg_left + 1;
  int xr = term.marg_right + 1;
  if (term.curs.origin) {

    xl = 1;
    xr = term.marg_right - term.marg_left + 1;
    y0 -= term.marg_top;
    y1 -= term.marg_top;
    y2 -= term.marg_top;
    e0 -= term.marg_top;
    e1 -= term.marg_top;
  }
  copy_rect(y0, xl, y1, xr, y2, xl);
  fill_rect(' ', term.curs.attr, false, e0, xl, e1, xr);
}
