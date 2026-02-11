setpagesize(s)
char* s;

{
  int i, j;

  pagelen = A4_PAGELEN - 2 * ymargin;
  pagewidth = A4_PAGEWIDTH - 2 * xmargin;
  if (s != NULL) {
    i = 0;
    j = 0;
    sscanf(s, "%dx%d", &i, &j);
    if (i == 0) {
      pagelen = A4_PAGELEN - 2 * ymargin;
      pagewidth = A4_PAGEWIDTH - 2 * xmargin;
    };
    if (i == 1) {
      pagelen = US_LETTER_PAGELEN - 2 * ymargin;
      pagewidth = US_LETTER_PAGEWIDTH - 2 * xmargin;
    };
    if ((i > 100) && (i > 2*xmargin) && (j > 100) && (j > 2*ymargin)) {
      pagewidth = i - 2 * xmargin;
      pagelen = j - 2 * ymargin;
    };
  };
  if (landscape) {
    i = xmargin;
    xmargin = ymargin;
    ymargin = i;
    i = pagelen;
    pagelen = pagewidth;
    pagewidth = i;
  };
  scaledlen = ((double)(pagelen))/scale;
  scaledwidth = ((double)(pagewidth))/scale;
}
