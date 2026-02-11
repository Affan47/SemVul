hns_rcb_get_base_irq_idx(struct rcb_common_cb *rcb_common)
{
	int comm_index = rcb_common->comm_index;

	if (comm_index == HNS_DSAF_COMM_SERVICE_NW_IDX)
		return HNS_SERVICE_RING_IRQ_IDX;
	else
		return HNS_DEBUG_RING_IRQ_IDX + (comm_index - 1) * 2;
}
