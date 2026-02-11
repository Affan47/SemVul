bump_free_buff_ring(u32 *free_buff_ring, u32 limit)
{
	u32 tmp_free_buff_ring = *free_buff_ring;

	tmp_free_buff_ring++;


	if ((tmp_free_buff_ring & ET_DMA10_MASK) > limit) {
		tmp_free_buff_ring &= ~ET_DMA10_MASK;
		tmp_free_buff_ring ^= ET_DMA10_WRAP;
	}

	tmp_free_buff_ring &= (ET_DMA10_MASK | ET_DMA10_WRAP);
	*free_buff_ring = tmp_free_buff_ring;
	return tmp_free_buff_ring;
}
