int bnx2x_init_hw_func_cnic(struct bnx2x *bp)
{
	int rc;

	bnx2x_ilt_init_op_cnic(bp, INITOP_SET);

	if (CONFIGURE_NIC_MODE(bp)) {

		bnx2x_init_searcher(bp);


		rc = bnx2x_reset_nic_mode(bp);
		if (rc)
			BNX2X_ERR("Can't change NIC mode!\n");
		return rc;
	}

	return 0;
}
