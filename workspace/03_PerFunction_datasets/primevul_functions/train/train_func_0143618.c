u16 sdma_get_descq_cnt(void)
{
	u16 count = sdma_descq_cnt;

	if (!count)
		return SDMA_DESCQ_CNT;


	if (!is_power_of_2(count))
		return SDMA_DESCQ_CNT;
	if (count < 64 || count > 32768)
		return SDMA_DESCQ_CNT;
	return count;
}
