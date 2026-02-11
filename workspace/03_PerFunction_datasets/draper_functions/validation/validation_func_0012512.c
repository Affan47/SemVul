esas2r_targ_db_get_tgt_cnt(struct esas2r_adapter *a)
{
	u16 devcnt = 0;
	struct esas2r_target *t;
	unsigned long flags;

	spin_lock_irqsave(&a->mem_lock, flags);
	for (t = a->targetdb; t < a->targetdb_end; t++)
		if (t->target_state == TS_PRESENT)
			devcnt++;

	spin_unlock_irqrestore(&a->mem_lock, flags);

	return devcnt;
}
