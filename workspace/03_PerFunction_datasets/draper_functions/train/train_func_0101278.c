fnv_zhash(ZVALUE z, QCKHASH val)
{
	LEN n;
	HALF *hp;
#if BASEB == 16
	FULL f;
#endif


	val += V_NUM;
	quasi_fnv(z.sign, val);

	n = z.len;
	hp = z.v;

#if BASEB == 16
	while (n > 1) {
		f = (FULL) *hp++;
		f |= (FULL) *hp++ << BASEB;
		quasi_fnv(f, val);
		n -= 2;
	}
	if (n) {
		quasi_fnv(*hp, val);
	}
#else
	while (n--  > 0) {
		quasi_fnv(*hp, val);
		++hp;
	}
#endif
	return val;
}
