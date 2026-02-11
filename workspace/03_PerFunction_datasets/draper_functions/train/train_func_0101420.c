efx_mcdi_flush_rxqs(struct efx_nic *efx)
{
	struct efx_channel *channel;
	struct efx_rx_queue *rx_queue;
	MCDI_DECLARE_BUF(inbuf,
			 MC_CMD_FLUSH_RX_QUEUES_IN_LEN(EFX_MAX_CHANNELS));
	int rc, count;

	BUILD_BUG_ON(EFX_MAX_CHANNELS >
		     MC_CMD_FLUSH_RX_QUEUES_IN_QID_OFST_MAXNUM);

	count = 0;
	efx_for_each_channel(channel, efx) {
		efx_for_each_channel_rx_queue(rx_queue, channel) {
			if (rx_queue->flush_pending) {
				rx_queue->flush_pending = false;
				atomic_dec(&efx->rxq_flush_pending);
				MCDI_SET_ARRAY_DWORD(
					inbuf, FLUSH_RX_QUEUES_IN_QID_OFST,
					count, efx_rx_queue_index(rx_queue));
				count++;
			}
		}
	}

	rc = efx_mcdi_rpc(efx, MC_CMD_FLUSH_RX_QUEUES, inbuf,
			  MC_CMD_FLUSH_RX_QUEUES_IN_LEN(count), NULL, 0, NULL);
	WARN_ON(rc < 0);

	return rc;
}
