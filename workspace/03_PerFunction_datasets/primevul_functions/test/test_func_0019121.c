static inline unsigned int lpf_count_to_us(unsigned int count)
{

	return DIV_ROUND_CLOSEST(count, CX23888_IR_REFCLK_FREQ / 1000000);
}
