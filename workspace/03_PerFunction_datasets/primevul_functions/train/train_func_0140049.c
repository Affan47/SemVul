static void bnx2x_get_fcoe_info(struct bnx2x *bp)
{
	int port = BP_PORT(bp);
	int func = BP_ABS_FUNC(bp);
	u32 max_fcoe_conn = FW_ENCODE_32BIT_PATTERN ^ SHMEM_RD(bp,
				drv_lic_key[port].max_fcoe_conn);
	u8 num_fcoe_func = bnx2x_shared_fcoe_funcs(bp);

	if (!CNIC_SUPPORT(bp)) {
		bp->flags |= NO_FCOE_FLAG;
		return;
	}


	bp->cnic_eth_dev.max_fcoe_conn =
		(max_fcoe_conn & BNX2X_MAX_FCOE_INIT_CONN_MASK) >>
		BNX2X_MAX_FCOE_INIT_CONN_SHIFT;


	bp->cnic_eth_dev.max_fcoe_exchanges = MAX_NUM_FCOE_TASKS_PER_ENGINE;


	if (num_fcoe_func)
		bp->cnic_eth_dev.max_fcoe_exchanges /= num_fcoe_func;


	if (!IS_MF(bp)) {

		bp->cnic_eth_dev.fcoe_wwn_port_name_hi =
			SHMEM_RD(bp,
				 dev_info.port_hw_config[port].
				 fcoe_wwn_port_name_upper);
		bp->cnic_eth_dev.fcoe_wwn_port_name_lo =
			SHMEM_RD(bp,
				 dev_info.port_hw_config[port].
				 fcoe_wwn_port_name_lower);


		bp->cnic_eth_dev.fcoe_wwn_node_name_hi =
			SHMEM_RD(bp,
				 dev_info.port_hw_config[port].
				 fcoe_wwn_node_name_upper);
		bp->cnic_eth_dev.fcoe_wwn_node_name_lo =
			SHMEM_RD(bp,
				 dev_info.port_hw_config[port].
				 fcoe_wwn_node_name_lower);
	} else if (!IS_MF_SD(bp)) {


		if (BNX2X_HAS_MF_EXT_PROTOCOL_FCOE(bp))
			bnx2x_get_ext_wwn_info(bp, func);
	} else {
		if (BNX2X_IS_MF_SD_PROTOCOL_FCOE(bp) && !CHIP_IS_E1x(bp))
			bnx2x_get_ext_wwn_info(bp, func);
	}

	BNX2X_DEV_INFO("max_fcoe_conn 0x%x\n", bp->cnic_eth_dev.max_fcoe_conn);


	if (!bp->cnic_eth_dev.max_fcoe_conn)
		bp->flags |= NO_FCOE_FLAG;
}
