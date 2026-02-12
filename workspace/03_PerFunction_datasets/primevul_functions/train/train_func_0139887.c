void bnx2x_chip_cleanup(struct bnx2x *bp, int unload_mode, bool keep_link)
{
	int port = BP_PORT(bp);
	int i, rc = 0;
	u8 cos;
	struct bnx2x_mcast_ramrod_params rparam = {NULL};
	u32 reset_code;


	for_each_tx_queue(bp, i) {
		struct bnx2x_fastpath *fp = &bp->fp[i];

		for_each_cos_in_tx_queue(fp, cos)
			rc = bnx2x_clean_tx_queue(bp, fp->txdata_ptr[cos]);
#ifdef BNX2X_STOP_ON_ERROR
		if (rc)
			return;
#endif
	}


	usleep_range(1000, 2000);


	rc = bnx2x_del_all_macs(bp, &bp->sp_objs[0].mac_obj, BNX2X_ETH_MAC,
				false);
	if (rc < 0)
		BNX2X_ERR("Failed to delete all ETH macs: %d\n", rc);


	rc = bnx2x_del_all_macs(bp, &bp->sp_objs[0].mac_obj, BNX2X_UC_LIST_MAC,
				true);
	if (rc < 0)
		BNX2X_ERR("Failed to schedule DEL commands for UC MACs list: %d\n",
			  rc);


	if (!CHIP_IS_E1(bp))
		REG_WR(bp, NIG_REG_LLH0_FUNC_EN + port*8, 0);


	netif_addr_lock_bh(bp->dev);

	if (test_bit(BNX2X_FILTER_RX_MODE_PENDING, &bp->sp_state))
		set_bit(BNX2X_FILTER_RX_MODE_SCHED, &bp->sp_state);
	else if (bp->slowpath)
		bnx2x_set_storm_rx_mode(bp);


	rparam.mcast_obj = &bp->mcast_obj;
	rc = bnx2x_config_mcast(bp, &rparam, BNX2X_MCAST_CMD_DEL);
	if (rc < 0)
		BNX2X_ERR("Failed to send DEL multicast command: %d\n", rc);

	netif_addr_unlock_bh(bp->dev);

	bnx2x_iov_chip_cleanup(bp);


	reset_code = bnx2x_send_unload_req(bp, unload_mode);


	rc = bnx2x_func_wait_started(bp);
	if (rc) {
		BNX2X_ERR("bnx2x_func_wait_started failed\n");
#ifdef BNX2X_STOP_ON_ERROR
		return;
#endif
	}


	for_each_eth_queue(bp, i)
		if (bnx2x_stop_queue(bp, i))
#ifdef BNX2X_STOP_ON_ERROR
			return;
#else
			goto unload_error;
#endif

	if (CNIC_LOADED(bp)) {
		for_each_cnic_queue(bp, i)
			if (bnx2x_stop_queue(bp, i))
#ifdef BNX2X_STOP_ON_ERROR
				return;
#else
				goto unload_error;
#endif
	}


	if (!bnx2x_wait_sp_comp(bp, ~0x0UL))
		BNX2X_ERR("Hmmm... Common slow path ramrods got stuck!\n");

#ifndef BNX2X_STOP_ON_ERROR
unload_error:
#endif
	rc = bnx2x_func_stop(bp);
	if (rc) {
		BNX2X_ERR("Function stop failed!\n");
#ifdef BNX2X_STOP_ON_ERROR
		return;
#endif
	}


	if (bp->flags & PTP_SUPPORTED)
		bnx2x_stop_ptp(bp);


	bnx2x_netif_stop(bp, 1);

	bnx2x_del_all_napi(bp);
	if (CNIC_LOADED(bp))
		bnx2x_del_all_napi_cnic(bp);


	bnx2x_free_irq(bp);


	if (!pci_channel_offline(bp->pdev)) {
		rc = bnx2x_reset_hw(bp, reset_code);
		if (rc)
			BNX2X_ERR("HW_RESET failed\n");
	}


	bnx2x_send_unload_done(bp, keep_link);
}
