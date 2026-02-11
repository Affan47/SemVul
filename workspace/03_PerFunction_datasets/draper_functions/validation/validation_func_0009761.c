bnx2x_compare_fw_ver(struct bnx2x *bp, u32 load_code, bool print_err)
{

	if (load_code != FW_MSG_CODE_DRV_LOAD_COMMON_CHIP &&
	    load_code != FW_MSG_CODE_DRV_LOAD_COMMON) {

		u32 my_fw = (BCM_5710_FW_MAJOR_VERSION) +
			(BCM_5710_FW_MINOR_VERSION << 8) +
			(BCM_5710_FW_REVISION_VERSION << 16) +
			(BCM_5710_FW_ENGINEERING_VERSION << 24);


		u32 loaded_fw = REG_RD(bp, XSEM_REG_PRAM);

		DP(BNX2X_MSG_SP, "loaded fw %x, my fw %x\n",
		   loaded_fw, my_fw);


		if (my_fw != loaded_fw) {
			if (print_err)
				BNX2X_ERR("bnx2x with FW %x was already loaded which mismatches my %x FW. Aborting\n",
					  loaded_fw, my_fw);
			else
				BNX2X_DEV_INFO("bnx2x with FW %x was already loaded which mismatches my %x FW, possibly due to MF UNDI\n",
					       loaded_fw, my_fw);
			return -EBUSY;
		}
	}
	return 0;
}
