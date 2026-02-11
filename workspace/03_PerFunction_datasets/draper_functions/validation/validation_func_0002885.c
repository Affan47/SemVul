find_closest ( tdmInteractor I, int x, int y )
{
  int i;
  DEFDATA(I,CursorData) ;

  ENTRY(("find_closest(0x%x, %d, %d)", I, x, y));

  if (PDATA(mode) == XmCURSOR_MODE) {
    for ( i = 0 ; i < PDATA(n_cursors) ; i++ )
      {
	if ( (abs (PDATA(xbuff)[i] - x) < PDATA(cursor_size)/2+1) &&
	    (abs (PDATA(ybuff)[i] - y) < PDATA(cursor_size)/2+1) ) {
	  EXIT(("%d",i));
	  return i;
	}
      }
  } else if (PDATA(mode) == XmROAM_MODE) {
    if ( (abs (PDATA(roam_xbuff) - x) < PDATA(cursor_size)/2+1) &&
	(abs (PDATA(roam_ybuff) - y) < PDATA(cursor_size)/2+1) ) {
      EXIT(("0"));
      return 0;
    }
  }

  EXIT(("-1"));
  return -1;
}
