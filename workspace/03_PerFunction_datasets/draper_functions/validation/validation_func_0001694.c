hfi1_dma_map_single(struct ib_device *dev, void *cpu_addr,
			       size_t size, enum dma_data_direction direction)
{
	if (WARN_ON(!valid_dma_direction(direction)))
		return BAD_DMA_ADDRESS;

	return (u64) cpu_addr;
}
