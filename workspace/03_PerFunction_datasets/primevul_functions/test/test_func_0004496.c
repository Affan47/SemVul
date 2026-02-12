i64 fmtutil_hlp_get_cul_p(dbuf *f, i64 *ppos)
{
	i64 x1, x2;
	x1 = dbuf_getu16le_p(f, ppos);
	if(x1%2 == 0) {

		return x1>>1;
	}


	x2 = dbuf_getu16le_p(f, ppos);
	return (x1>>1) | (x2<<15);
}
