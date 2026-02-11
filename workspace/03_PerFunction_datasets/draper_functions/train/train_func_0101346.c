iser_alloc_rx_descriptors(struct iser_conn *iser_conn,
			      struct iscsi_session *session)
{
	int i, j;
	u64 dma_addr;
	struct iser_rx_desc *rx_desc;
	struct ib_sge       *rx_sg;
	struct ib_conn *ib_conn = &iser_conn->ib_conn;
	struct iser_device *device = ib_conn->device;

	iser_conn->qp_max_recv_dtos = session->cmds_max;
	iser_conn->qp_max_recv_dtos_mask = session->cmds_max - 1;
	iser_conn->min_posted_rx = iser_conn->qp_max_recv_dtos >> 2;

	if (device->reg_ops->alloc_reg_res(ib_conn, session->scsi_cmds_max,
					   iser_conn->scsi_sg_tablesize))
		goto create_rdma_reg_res_failed;

	if (iser_alloc_login_buf(iser_conn))
		goto alloc_login_buf_fail;

	iser_conn->num_rx_descs = session->cmds_max;
	iser_conn->rx_descs = kmalloc(iser_conn->num_rx_descs *
				sizeof(struct iser_rx_desc), GFP_KERNEL);
	if (!iser_conn->rx_descs)
		goto rx_desc_alloc_fail;

	rx_desc = iser_conn->rx_descs;

	for (i = 0; i < iser_conn->qp_max_recv_dtos; i++, rx_desc++)  {
		dma_addr = ib_dma_map_single(device->ib_device, (void *)rx_desc,
					ISER_RX_PAYLOAD_SIZE, DMA_FROM_DEVICE);
		if (ib_dma_mapping_error(device->ib_device, dma_addr))
			goto rx_desc_dma_map_failed;

		rx_desc->dma_addr = dma_addr;

		rx_sg = &rx_desc->rx_sg;
		rx_sg->addr   = rx_desc->dma_addr;
		rx_sg->length = ISER_RX_PAYLOAD_SIZE;
		rx_sg->lkey   = device->pd->local_dma_lkey;
	}

	iser_conn->rx_desc_head = 0;
	return 0;

rx_desc_dma_map_failed:
	rx_desc = iser_conn->rx_descs;
	for (j = 0; j < i; j++, rx_desc++)
		ib_dma_unmap_single(device->ib_device, rx_desc->dma_addr,
				    ISER_RX_PAYLOAD_SIZE, DMA_FROM_DEVICE);
	kfree(iser_conn->rx_descs);
	iser_conn->rx_descs = NULL;
rx_desc_alloc_fail:
	iser_free_login_buf(iser_conn);
alloc_login_buf_fail:
	device->reg_ops->free_reg_res(ib_conn);
create_rdma_reg_res_failed:
	iser_err("failed allocating rx descriptors / data buffers\n");
	return -ENOMEM;
}
