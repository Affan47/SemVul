async_dma_map(struct virtio_net *dev, bool do_map)
{
	int ret = 0;
	uint32_t i;
	struct guest_page *page;

	if (do_map) {
		for (i = 0; i < dev->nr_guest_pages; i++) {
			page = &dev->guest_pages[i];
			ret = rte_vfio_container_dma_map(RTE_VFIO_DEFAULT_CONTAINER_FD,
							 page->host_user_addr,
							 page->host_iova,
							 page->size);
			if (ret) {


				if (rte_errno == ENODEV)
					return;


				VHOST_LOG_CONFIG(ERR, "DMA engine map failed\n");
			}
		}

	} else {
		for (i = 0; i < dev->nr_guest_pages; i++) {
			page = &dev->guest_pages[i];
			ret = rte_vfio_container_dma_unmap(RTE_VFIO_DEFAULT_CONTAINER_FD,
							   page->host_user_addr,
							   page->host_iova,
							   page->size);
			if (ret) {

				if (rte_errno == EINVAL)
					return;

				VHOST_LOG_CONFIG(ERR, "DMA engine unmap failed\n");
			}
		}
	}
}
