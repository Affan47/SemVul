bnx2x_common_init_phy(struct bnx2x *bp, u32 shmem_base_path[],
			  u32 shmem2_base_path[], u32 chip_id)
{
	int rc = 0;
	u32 phy_ver, val;
	u8 phy_index = 0;
	u32 ext_phy_type, ext_phy_config;

	bnx2x_set_mdio_clk(bp, chip_id, GRCBASE_EMAC0);
	bnx2x_set_mdio_clk(bp, chip_id, GRCBASE_EMAC1);
	DP(NETIF_MSG_LINK, "Begin common phy init\n");
	if (CHIP_IS_E3(bp)) {

		val = REG_RD(bp, MISC_REG_GEN_PURP_HWG);
		REG_WR(bp, MISC_REG_GEN_PURP_HWG, val | 1);
	}

	phy_ver = REG_RD(bp, shmem_base_path[0] +
			 offsetof(struct shmem_region,
				  port_mb[PORT_0].ext_phy_fw_version));
	if (phy_ver) {
		DP(NETIF_MSG_LINK, "Not doing common init; phy ver is 0x%x\n",
			       phy_ver);
		return 0;
	}


	for (phy_index = EXT_PHY1; phy_index < MAX_PHYS;
	      phy_index++) {
		ext_phy_config = bnx2x_get_ext_phy_config(bp,
							  shmem_base_path[0],
							  phy_index, 0);
		ext_phy_type = XGXS_EXT_PHY_TYPE(ext_phy_config);
		rc |= bnx2x_ext_phy_common_init(bp, shmem_base_path,
						shmem2_base_path,
						phy_index, ext_phy_type,
						chip_id);
	}
	return rc;
}
