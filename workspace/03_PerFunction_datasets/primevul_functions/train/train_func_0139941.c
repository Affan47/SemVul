static void bnx2x_mcp_wait_one(struct bnx2x *bp)
{


	if (CHIP_REV_IS_SLOW(bp))
		msleep(MCP_ONE_TIMEOUT*10);
	else
		msleep(MCP_ONE_TIMEOUT);
}
