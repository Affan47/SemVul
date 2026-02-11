timer_callback(int which)
{
	if (LOG_GALILEO)
		logerror("timer %d fired\n", which);


	timer_count[which] = galileo_regs[0x850/4 + which];
	if (which != 0)
		timer_count[which] &= 0xffffff;


	if (galileo_regs[0x864/4] & (2 << (2 * which)))
		timer_adjust(timer[which], TIMER_CLOCK * timer_count[which], which, 0);
	else
		timer_active[which] = timer_count[which] = 0;


	galileo_regs[0xc18/4] |= 0x100 << which;
	update_galileo_irqs();
}
