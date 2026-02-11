irq_gc_set_wake(struct irq_data *d, unsigned int on)
{
	struct irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	u32 mask = d->mask;

	if (!(mask & gc->wake_enabled))
		return -EINVAL;

	irq_gc_lock(gc);
	if (on)
		gc->wake_active |= mask;
	else
		gc->wake_active &= ~mask;
	irq_gc_unlock(gc);
	return 0;
}
