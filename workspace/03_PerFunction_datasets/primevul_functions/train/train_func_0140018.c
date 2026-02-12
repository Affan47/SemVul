static int bnx2x_init_hw_common_chip(struct bnx2x *bp)
{
	int rc = bnx2x_init_hw_common(bp);

	if (rc)
		return rc;


	if (!BP_NOMCP(bp))
		bnx2x__common_init_phy(bp);

	return 0;
}
