void speculation_ctrl_update(unsigned long tif)
{
	unsigned long flags;


	local_irq_save(flags);
	__speculation_ctrl_update(~tif, tif);
	local_irq_restore(flags);
}
