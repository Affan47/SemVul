void speculative_store_bypass_ht_init(void)
{
	struct ssb_state *st = this_cpu_ptr(&ssb_state);
	unsigned int this_cpu = smp_processor_id();
	unsigned int cpu;

	st->local_state = 0;


	if (st->shared_state)
		return;

	raw_spin_lock_init(&st->lock);


	for_each_cpu(cpu, topology_sibling_cpumask(this_cpu)) {
		if (cpu == this_cpu)
			continue;

		if (!per_cpu(ssb_state, cpu).shared_state)
			continue;


		st->shared_state = per_cpu(ssb_state, cpu).shared_state;
		return;
	}


	st->shared_state = st;
}
