igb_run_loopback_test(struct igb_adapter *adapter)
{
	struct igb_ring *tx_ring = &adapter->test_tx_ring;
	struct igb_ring *rx_ring = &adapter->test_rx_ring;
	u16 i, j, lc, good_cnt;
	int ret_val = 0;
	unsigned int size = IGB_RX_HDR_LEN;
	netdev_tx_t tx_ret_val;
	struct sk_buff *skb;


	skb = alloc_skb(size, GFP_KERNEL);
	if (!skb)
		return 11;


	igb_create_lbtest_frame(skb, size);
	skb_put(skb, size);


	if (rx_ring->count <= tx_ring->count)
		lc = ((tx_ring->count / 64) * 2) + 1;
	else
		lc = ((rx_ring->count / 64) * 2) + 1;

	for (j = 0; j <= lc; j++) {

		good_cnt = 0;


		for (i = 0; i < 64; i++) {
			skb_get(skb);
			tx_ret_val = igb_xmit_frame_ring(skb, tx_ring);
			if (tx_ret_val == NETDEV_TX_OK)
				good_cnt++;
		}

		if (good_cnt != 64) {
			ret_val = 12;
			break;
		}


		msleep(200);

		good_cnt = igb_clean_test_rings(rx_ring, tx_ring, size);
		if (good_cnt != 64) {
			ret_val = 13;
			break;
		}
	}


	kfree_skb(skb);

	return ret_val;
}
