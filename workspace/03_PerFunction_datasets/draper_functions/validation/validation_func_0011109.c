tmr_reset(void)
{
	unsigned long   flags;

	spin_lock_irqsave(&lock,flags);
	tmr_offs = 0;
	ticks_offs = 0;
	tmr_ctr = 0;
	next_event_time = (unsigned long) -1;
	prev_event_time = 0;
	curr_ticks = 0;
	spin_unlock_irqrestore(&lock,flags);
}
