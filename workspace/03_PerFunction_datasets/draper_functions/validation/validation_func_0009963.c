forwdel(int f, int n)
{
    if (curbp->b_mode&MDVIEW)
      return(rdonly());

    if (n < 0)
      return (backdel(f, -n));

    if(TERM_OPTIMIZE && (curwp->w_dotp != curwp->w_bufp->b_linep)){
	int l;

	if(worthit(&l) && curwp->w_doto == llength(curwp->w_dotp))
	  scrollup(curwp, l+1, 1);
    }

    if (f != FALSE) {
	if ((lastflag&CFKILL) == 0)
	  kdelete();
	thisflag |= CFKILL;
    }

    return (ldelete((long) n, f ? kinsert : NULL));
}
