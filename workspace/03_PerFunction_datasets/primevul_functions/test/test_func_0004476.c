i64 fmtutil_hlp_get_cus_p(dbuf *f, i64 *ppos)
{
	i64 x1, x2;

	x1 = (i64)dbuf_getbyte_p(f, ppos);
	if(x1%2 == 0) {

		return x1>>1;
	}


	x2 = (i64)dbuf_getbyte_p(f, ppos);
	return (x1>>1) | (x2<<7);
}
