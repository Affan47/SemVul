efx_alloc_channel(struct efx_nic *efx, int i, struct efx_channel *old_channel)
{
	struct efx_channel *channel;
	struct efx_rx_queue *rx_queue;
	struct efx_tx_queue *tx_queue;
	int j;

	channel = kzalloc(sizeof(*channel), GFP_KERNEL);
	if (!channel)
		return NULL;

	channel->efx = efx;
	channel->channel = i;
	channel->type = &efx_default_channel_type;

	for (j = 0; j < EFX_TXQ_TYPES; j++) {
		tx_queue = &channel->tx_queue[j];
		tx_queue->efx = efx;
		tx_queue->queue = i * EFX_TXQ_TYPES + j;
		tx_queue->channel = channel;
	}

	rx_queue = &channel->rx_queue;
	rx_queue->efx = efx;
	setup_timer(&rx_queue->slow_fill, efx_rx_slow_fill,
		    (unsigned long)rx_queue);

	return channel;
}
