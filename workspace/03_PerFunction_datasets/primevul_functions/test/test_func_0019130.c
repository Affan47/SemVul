static inline unsigned int clock_divider_to_ns(unsigned int divider)
{

	return DIV_ROUND_CLOSEST((divider + 1) * 1000,
				 CX23888_IR_REFCLK_FREQ / 1000000);
}
