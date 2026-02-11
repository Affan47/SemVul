v_e_math_inv(VBigDig *inv, const VBigDig *u, const VBigDig *v)
{
	VBigDig	VBIGNUM(u1, 2*BITS), VBIGNUM(u3, 2*BITS), VBIGNUM(v1, 2*BITS), VBIGNUM(v3, 2 *BITS),
		VBIGNUM(t1, 2*BITS), VBIGNUM(t3, 2*BITS), VBIGNUM(q, 2*BITS),  VBIGNUM(w, 2*BITS);
	int	iter = 1;

	v_bignum_set_one(u1);
	v_bignum_set_bignum(u3, u);
	v_bignum_set_zero(v1);
	v_bignum_set_bignum(v3, v);

	while(!v_bignum_eq_zero(v3))
	{
		v_bignum_set_bignum(q, u3);
		v_bignum_div(q, v3, t3);
		v_bignum_set_bignum(w, q);
		v_bignum_mul(w, v1);
		v_bignum_set_bignum(t1, u1);
		v_bignum_add(t1, w);

		v_bignum_set_bignum(u1, v1);
		v_bignum_set_bignum(v1, t1);
		v_bignum_set_bignum(u3, v3);
		v_bignum_set_bignum(v3, t3);
		iter = -iter;
	}
	if(iter < 0)
	{
		v_bignum_set_bignum(inv, v);
		v_bignum_sub(inv, u1);
	}
	else
		v_bignum_set_bignum(inv, u1);
}
