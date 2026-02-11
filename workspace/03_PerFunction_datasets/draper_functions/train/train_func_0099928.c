dirty(struct xio_win *xw, int y1, int y2)
{
    if (y1 >= 0 && y1 < H && y1 < y2)
    {
	if (y2 > H)
	    y2 = H;
	if (xw->hidden & (1 << y1))
	    y1--;
	while (y1 < y2)
	    xw->modified |= 1 << y1++;
    }
}
