void bnx2x_set_rx_mode_inner(struct bnx2x *bp)
{
	u32 rx_mode = BNX2X_RX_MODE_NORMAL;

	DP(NETIF_MSG_IFUP, "dev->flags = %x\n", bp->dev->flags);

	netif_addr_lock_bh(bp->dev);

	if (bp->dev->flags & IFF_PROMISC) {
		rx_mode = BNX2X_RX_MODE_PROMISC;
	} else if ((bp->dev->flags & IFF_ALLMULTI) ||
		   ((netdev_mc_count(bp->dev) > BNX2X_MAX_MULTICAST) &&
		    CHIP_IS_E1(bp))) {
		rx_mode = BNX2X_RX_MODE_ALLMULTI;
	} else {
		if (IS_PF(bp)) {

			if (bnx2x_set_mc_list(bp) < 0)
				rx_mode = BNX2X_RX_MODE_ALLMULTI;


			netif_addr_unlock_bh(bp->dev);
			if (bnx2x_set_uc_list(bp) < 0)
				rx_mode = BNX2X_RX_MODE_PROMISC;
			netif_addr_lock_bh(bp->dev);
		} else {


			bnx2x_schedule_sp_rtnl(bp,
					       BNX2X_SP_RTNL_VFPF_MCAST, 0);
		}
	}

	bp->rx_mode = rx_mode;

	if (IS_MF_ISCSI_ONLY(bp))
		bp->rx_mode = BNX2X_RX_MODE_NONE;


	if (test_bit(BNX2X_FILTER_RX_MODE_PENDING, &bp->sp_state)) {
		set_bit(BNX2X_FILTER_RX_MODE_SCHED, &bp->sp_state);
		netif_addr_unlock_bh(bp->dev);
		return;
	}

	if (IS_PF(bp)) {
		bnx2x_set_storm_rx_mode(bp);
		netif_addr_unlock_bh(bp->dev);
	} else {


		netif_addr_unlock_bh(bp->dev);
		bnx2x_vfpf_storm_rx_mode(bp);
	}
}
