alloc_cs(struct gigaset_driver *drv)
{
	unsigned long flags;
	unsigned i;
	struct cardstate *cs;
	struct cardstate *ret = NULL;

	spin_lock_irqsave(&drv->lock, flags);
	if (drv->blocked)
		goto exit;
	for (i = 0; i < drv->minors; ++i) {
		cs = drv->cs + i;
		if (!(cs->flags & VALID_MINOR)) {
			cs->flags = VALID_MINOR;
			ret = cs;
			break;
		}
	}
exit:
	spin_unlock_irqrestore(&drv->lock, flags);
	return ret;
}
