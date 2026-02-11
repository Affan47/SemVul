update_timer(int which)
{

	int base = 0x10 * which;
	int enabled = ((tms32031_io_regs[base + TIMER0_GLOBAL_CTL] & 0xc0) == 0xc0);


	if (enabled && !timer_enabled[which])
	{
		double period = cage_cpu_h1_clock * 2. * (double)tms32031_io_regs[base + TIMER0_PERIOD];


		if (tms32031_io_regs[base + TIMER0_GLOBAL_CTL] != 0x2c1)
			logerror("CAGE TIMER%d: unexpected timer config %08X!\n", which, tms32031_io_regs[base + TIMER0_GLOBAL_CTL]);

		timer_adjust(timer[which], period, which, TIME_NEVER);
	}


	else if (!enabled && timer_enabled[which])
	{
		timer_adjust(timer[which], TIME_NEVER, which, TIME_NEVER);
	}


	timer_enabled[which] = enabled;
}
