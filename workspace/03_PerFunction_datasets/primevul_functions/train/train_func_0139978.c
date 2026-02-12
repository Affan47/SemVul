static void bnx2x_get_cnic_mac_hwinfo(struct bnx2x *bp)
{
	u32 val, val2;
	int func = BP_ABS_FUNC(bp);
	int port = BP_PORT(bp);
	u8 *iscsi_mac = bp->cnic_eth_dev.iscsi_mac;
	u8 *fip_mac = bp->fip_mac;

	if (IS_MF(bp)) {


		if (!IS_MF_SD(bp)) {
			u32 cfg = MF_CFG_RD(bp, func_ext_config[func].func_cfg);
			if (cfg & MACP_FUNC_CFG_FLAGS_ISCSI_OFFLOAD) {
				val2 = MF_CFG_RD(bp, func_ext_config[func].
						 iscsi_mac_addr_upper);
				val = MF_CFG_RD(bp, func_ext_config[func].
						iscsi_mac_addr_lower);
				bnx2x_set_mac_buf(iscsi_mac, val, val2);
				BNX2X_DEV_INFO
					("Read iSCSI MAC: %pM\n", iscsi_mac);
			} else {
				bp->flags |= NO_ISCSI_OOO_FLAG | NO_ISCSI_FLAG;
			}

			if (cfg & MACP_FUNC_CFG_FLAGS_FCOE_OFFLOAD) {
				val2 = MF_CFG_RD(bp, func_ext_config[func].
						 fcoe_mac_addr_upper);
				val = MF_CFG_RD(bp, func_ext_config[func].
						fcoe_mac_addr_lower);
				bnx2x_set_mac_buf(fip_mac, val, val2);
				BNX2X_DEV_INFO
					("Read FCoE L2 MAC: %pM\n", fip_mac);
			} else {
				bp->flags |= NO_FCOE_FLAG;
			}

			bp->mf_ext_config = cfg;

		} else {
			if (BNX2X_IS_MF_SD_PROTOCOL_ISCSI(bp)) {

				memcpy(iscsi_mac, bp->dev->dev_addr, ETH_ALEN);

				BNX2X_DEV_INFO("SD ISCSI MODE\n");
				BNX2X_DEV_INFO
					("Read iSCSI MAC: %pM\n", iscsi_mac);
			} else if (BNX2X_IS_MF_SD_PROTOCOL_FCOE(bp)) {

				memcpy(fip_mac, bp->dev->dev_addr, ETH_ALEN);
				BNX2X_DEV_INFO("SD FCoE MODE\n");
				BNX2X_DEV_INFO
					("Read FIP MAC: %pM\n", fip_mac);
			}
		}


		if (IS_MF_FCOE_AFEX(bp))
			memcpy(bp->dev->dev_addr, fip_mac, ETH_ALEN);
	} else {
		val2 = SHMEM_RD(bp, dev_info.port_hw_config[port].
				iscsi_mac_upper);
		val = SHMEM_RD(bp, dev_info.port_hw_config[port].
			       iscsi_mac_lower);
		bnx2x_set_mac_buf(iscsi_mac, val, val2);

		val2 = SHMEM_RD(bp, dev_info.port_hw_config[port].
				fcoe_fip_mac_upper);
		val = SHMEM_RD(bp, dev_info.port_hw_config[port].
			       fcoe_fip_mac_lower);
		bnx2x_set_mac_buf(fip_mac, val, val2);
	}


	if (!is_valid_ether_addr(iscsi_mac)) {
		bp->flags |= NO_ISCSI_OOO_FLAG | NO_ISCSI_FLAG;
		eth_zero_addr(iscsi_mac);
	}


	if (!is_valid_ether_addr(fip_mac)) {
		bp->flags |= NO_FCOE_FLAG;
		eth_zero_addr(bp->fip_mac);
	}
}
