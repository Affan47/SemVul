static void bnx2x_reset_mcp_prep(struct bnx2x *bp, u32 *magic_val)
{
	u32 shmem;
	u32 validity_offset;

	DP(NETIF_MSG_HW | NETIF_MSG_IFUP, "Starting\n");


	if (!CHIP_IS_E1(bp))
		bnx2x_clp_reset_prep(bp, magic_val);


	shmem = REG_RD(bp, MISC_REG_SHARED_MEM_ADDR);
	validity_offset =
		offsetof(struct shmem_region, validity_map[BP_PORT(bp)]);


	if (shmem > 0)
		REG_WR(bp, shmem + validity_offset, 0);
}
