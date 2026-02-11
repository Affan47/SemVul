lockup_detected(struct ctlr_info *h)
{
	int cpu;
	u32 rc, *lockup_detected;

	cpu = get_cpu();
	lockup_detected = per_cpu_ptr(h->lockup_detected, cpu);
	rc = *lockup_detected;
	put_cpu();
	return rc;
}
