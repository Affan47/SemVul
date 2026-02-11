tb_ctl_free(struct tb_ctl *ctl)
{
	int i;
	if (ctl->rx)
		ring_free(ctl->rx);
	if (ctl->tx)
		ring_free(ctl->tx);


	for (i = 0; i < TB_CTL_RX_PKG_COUNT; i++)
		tb_ctl_pkg_free(ctl->rx_packets[i]);


	if (ctl->frame_pool)
		dma_pool_destroy(ctl->frame_pool);
	kfree(ctl);
}
