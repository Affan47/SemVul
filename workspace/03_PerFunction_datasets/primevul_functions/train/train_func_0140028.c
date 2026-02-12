static int bnx2x_prev_unload(struct bnx2x *bp)
{
	int time_counter = 10;
	u32 rc, fw, hw_lock_reg, hw_lock_val;
	BNX2X_DEV_INFO("Entering Previous Unload Flow\n");


	bnx2x_clean_pglue_errors(bp);


	hw_lock_reg = (BP_FUNC(bp) <= 5) ?
		      (MISC_REG_DRIVER_CONTROL_1 + BP_FUNC(bp) * 8) :
		      (MISC_REG_DRIVER_CONTROL_7 + (BP_FUNC(bp) - 6) * 8);

	hw_lock_val = REG_RD(bp, hw_lock_reg);
	if (hw_lock_val) {
		if (hw_lock_val & HW_LOCK_RESOURCE_NVRAM) {
			BNX2X_DEV_INFO("Release Previously held NVRAM lock\n");
			REG_WR(bp, MCP_REG_MCPR_NVM_SW_ARB,
			       (MCPR_NVM_SW_ARB_ARB_REQ_CLR1 << BP_PORT(bp)));
		}

		BNX2X_DEV_INFO("Release Previously held hw lock\n");
		REG_WR(bp, hw_lock_reg, 0xffffffff);
	} else
		BNX2X_DEV_INFO("No need to release hw/nvram locks\n");

	if (MCPR_ACCESS_LOCK_LOCK & REG_RD(bp, MCP_REG_MCPR_ACCESS_LOCK)) {
		BNX2X_DEV_INFO("Release previously held alr\n");
		bnx2x_release_alr(bp);
	}

	do {
		int aer = 0;

		fw = bnx2x_fw_command(bp, DRV_MSG_CODE_UNLOAD_REQ_WOL_DIS, 0);
		if (!fw) {
			BNX2X_ERR("MCP response failure, aborting\n");
			rc = -EBUSY;
			break;
		}

		rc = down_interruptible(&bnx2x_prev_sem);
		if (rc) {
			BNX2X_ERR("Cannot check for AER; Received %d when tried to take lock\n",
				  rc);
		} else {

			aer = !!(bnx2x_prev_path_get_entry(bp) &&
				 bnx2x_prev_path_get_entry(bp)->aer);
			up(&bnx2x_prev_sem);
		}

		if (fw == FW_MSG_CODE_DRV_UNLOAD_COMMON || aer) {
			rc = bnx2x_prev_unload_common(bp);
			break;
		}


		rc = bnx2x_prev_unload_uncommon(bp);
		if (rc != BNX2X_PREV_WAIT_NEEDED)
			break;

		msleep(20);
	} while (--time_counter);

	if (!time_counter || rc) {
		BNX2X_DEV_INFO("Unloading previous driver did not occur, Possibly due to MF UNDI\n");
		rc = -EPROBE_DEFER;
	}


	if (bnx2x_port_after_undi(bp))
		bp->link_params.feature_config_flags |=
			FEATURE_CONFIG_BOOT_FROM_SAN;

	BNX2X_DEV_INFO("Finished Previous Unload Flow [%d]\n", rc);

	return rc;
}
