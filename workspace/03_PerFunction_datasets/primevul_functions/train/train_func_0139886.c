static void bnx2x_update_eq_prod(struct bnx2x *bp, u16 prod)
{

	storm_memset_eq_prod(bp, prod, BP_FUNC(bp));
	mmiowb();
}
