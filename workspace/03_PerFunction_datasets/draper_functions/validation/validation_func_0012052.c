zgcdrem(ZVALUE z1, ZVALUE z2, ZVALUE *res)
{
	ZVALUE tmp1, tmp2;
	long count, onecount;
	long sh;

	if (ziszero(z1) || ziszero(z2)) {
		math_error("Zero argument in call to zgcdrem!!!");

	}


	z1.sign = 0;
	z2.sign = 0;
	if (zisone(z2))
		return 0;
	if (zisonebit(z2)) {
		sh = zlowbit(z1);
		if (sh == 0)
			return 0;
		zshift(z1, -sh, res);
		return 1 + (sh - 1)/zlowbit(z2);
	}
	if (zisonebit(z1)) {
		if (zisodd(z2))
			return 0;
		*res = _one_;
		return zlowbit(z1);
	}

	zgcd(z1, z2, &tmp1);
	if (zisunit(tmp1) || ziszero(tmp1))
		return 0;
	zequo(z1, tmp1, &tmp2);
	count = 1;
	z1 = tmp2;
	z2 = tmp1;


	while (!zisunit(z2)) {
		onecount = zfacrem(z1, z2, &tmp1);
		if (onecount) {
			count += onecount;
			zfree(z1);
			z1 = tmp1;
		}
		zgcd(z1, z2, &tmp1);
		zfree(z2);
		z2 = tmp1;
	}
	*res = z1;
	return count;
}
