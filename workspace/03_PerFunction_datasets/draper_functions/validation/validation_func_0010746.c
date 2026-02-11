butWin_findButsInRegion(ButWin *win, int x,int y, int w,int h,
			      bool (*action)(But *but, void *packet),
			      void *packet)  {
  int  r, c, b;
  ButCol  *col;
  ButRow  *row;
  But *but;

  assert(MAGIC(win));
  for (c = 1;  c < win->numCols - 1;  ++c)  {
    col = &win->cols[c];
    assert(MAGIC(col));
    if ((col->startX < x+w) && (win->cols[c+1].startX > x))  {
      for (r = 1;  r < col->numRows - 1;  ++r)  {
	row = &col->rows[r];
	assert(MAGIC(row));
	if ((row->startY < y+h) && (col->rows[r+1].startY > y))  {
	  for (b = 0;  b < row->numButs;  ++b)  {
	    but = row->buts[b];
	    assert(MAGIC(but));
	    if (action(but, packet))
	      return(but);
	  }
	}
      }
    }
  }
  return(NULL);
}
