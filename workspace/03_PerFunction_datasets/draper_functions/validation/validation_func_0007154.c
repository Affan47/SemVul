backchar_no_header_editor(int f, int n)
{
    register LINE   *lp;

    if (n < 0)
      return (forwchar(f, -n));

    while (n--) {
	if (curwp->w_doto == 0) {
	    if ((lp=lback(curwp->w_dotp)) == curbp->b_linep){
		  return (FALSE);
	    }

	    curwp->w_dotp  = lp;
	    curwp->w_doto  = llength(lp);
	    curwp->w_flag |= WFMOVE;
	} else
	  curwp->w_doto--;
    }

    return (TRUE);
}
