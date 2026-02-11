lockdep_reset(void)
{
	unsigned long flags;
	int i;

	raw_local_irq_save(flags);
	current->curr_chain_key = 0;
	current->lockdep_depth = 0;
	current->lockdep_recursion = 0;
	memset(current->held_locks, 0, MAX_LOCK_DEPTH*sizeof(struct held_lock));
	nr_hardirq_chains = 0;
	nr_softirq_chains = 0;
	nr_process_chains = 0;
	debug_locks = 1;
	for (i = 0; i < CHAINHASH_SIZE; i++)
		INIT_LIST_HEAD(chainhash_table + i);
	raw_local_irq_restore(flags);
}
