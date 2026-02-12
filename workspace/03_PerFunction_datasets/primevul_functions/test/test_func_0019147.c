static u64 ns_to_pulse_clocks(u32 ns)
{
	u64 clocks;
	u32 rem;
	clocks = CX23888_IR_REFCLK_FREQ / 1000000 * (u64) ns;
	rem = do_div(clocks, 1000);
	if (rem >= 1000 / 2)
		clocks++;
	return clocks;
}
