static void mce_reign(void)
{
	int cpu;
	struct mce *m = NULL;
	int global_worst = 0;
	char *msg = NULL;
	char *nmsg = NULL;


	for_each_possible_cpu(cpu) {
		int severity = mce_severity(&per_cpu(mces_seen, cpu),
					    mca_cfg.tolerant,
					    &nmsg, true);
		if (severity > global_worst) {
			msg = nmsg;
			global_worst = severity;
			m = &per_cpu(mces_seen, cpu);
		}
	}


	if (m && global_worst >= MCE_PANIC_SEVERITY && mca_cfg.tolerant < 3)
		mce_panic("Fatal machine check", m, msg);


	if (global_worst <= MCE_KEEP_SEVERITY && mca_cfg.tolerant < 3)
		mce_panic("Fatal machine check from unknown source", NULL, NULL);


	for_each_possible_cpu(cpu)
		memset(&per_cpu(mces_seen, cpu), 0, sizeof(struct mce));
}
