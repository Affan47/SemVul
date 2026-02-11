display16_lookup(int d16_ix, ucs4_t ucs4)
{
    	int row, col;
	int ix;


    	if (d16_ix < 0)
		return -1;


	if (d16_ix == ISO10646_IX)
		return (int)ucs4;


	if ((unsigned)d16_ix >= (ND16 - 1))
	    	return -1;


	if (ucs4 > 0xffff)
	    	return -1;
	row = (ucs4 >> 7) & 0x1ff;
	if (d16[d16_ix].u[row] == NULL)
	    	return -1;

	col = (ucs4 & 0x7f) * 2;
	ix = ((d16[d16_ix].u[row][col] & 0xff) << 8) |
	      (d16[d16_ix].u[row][col + 1] & 0xff);
	if (ix != 0)
	    return ix;


	return -1;
}
