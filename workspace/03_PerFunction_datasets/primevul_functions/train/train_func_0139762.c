static int bnx2x_prev_unload_uncommon(struct bnx2x *bp)
{
	int rc;

	BNX2X_DEV_INFO("Uncommon unload Flow\n");


	if (bnx2x_prev_is_path_marked(bp))
		return bnx2x_prev_mcp_done(bp);

	BNX2X_DEV_INFO("Path is unmarked\n");


	if (bnx2x_prev_is_after_undi(bp))
		goto out;


	rc = bnx2x_compare_fw_ver(bp, FW_MSG_CODE_DRV_LOAD_FUNCTION, false);

	if (!rc) {

		BNX2X_DEV_INFO("FW version matches our own. Attempting FLR\n");
		rc = bnx2x_do_flr(bp);
	}

	if (!rc) {

		BNX2X_DEV_INFO("FLR successful\n");
		return 0;
	}

	BNX2X_DEV_INFO("Could not FLR\n");

out:

	rc = bnx2x_prev_mcp_done(bp);
	if (!rc)
		rc = BNX2X_PREV_WAIT_NEEDED;

	return rc;
}
