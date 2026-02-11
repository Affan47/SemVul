vxge_hw_ring_replenish(struct __vxge_hw_ring *ring)
{
	void *rxd;
	struct __vxge_hw_channel *channel;
	enum vxge_hw_status status = VXGE_HW_OK;

	channel = &ring->channel;

	while (vxge_hw_channel_dtr_count(channel) > 0) {

		status = vxge_hw_ring_rxd_reserve(ring, &rxd);

		vxge_assert(status == VXGE_HW_OK);

		if (ring->rxd_init) {
			status = ring->rxd_init(rxd, channel->userdata);
			if (status != VXGE_HW_OK) {
				vxge_hw_ring_rxd_free(ring, rxd);
				goto exit;
			}
		}

		vxge_hw_ring_rxd_post(ring, rxd);
	}
	status = VXGE_HW_OK;
exit:
	return status;
}
