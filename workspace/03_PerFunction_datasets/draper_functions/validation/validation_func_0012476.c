bnad_napi_delete(struct bnad *bnad, u32 rx_id)
{
	int i;


	for (i = 0; i < bnad->num_rxp_per_rx; i++)
		netif_napi_del(&bnad->rx_info[rx_id].rx_ctrl[i].napi);
}
