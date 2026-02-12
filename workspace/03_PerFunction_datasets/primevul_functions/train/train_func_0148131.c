__visible void kvm_lock_spinning(struct arch_spinlock *lock, __ticket_t want)
{
	struct kvm_lock_waiting *w;
	int cpu;
	u64 start;
	unsigned long flags;

	if (in_nmi())
		return;

	w = this_cpu_ptr(&klock_waiting);
	cpu = smp_processor_id();
	start = spin_time_start();


	local_irq_save(flags);


	w->lock = NULL;
	smp_wmb();
	w->want = want;
	smp_wmb();
	w->lock = lock;

	add_stats(TAKEN_SLOW, 1);


	cpumask_set_cpu(cpu, &waiting_cpus);

	barrier();


	__ticket_enter_slowpath(lock);


	if (ACCESS_ONCE(lock->tickets.head) == want) {
		add_stats(TAKEN_SLOW_PICKUP, 1);
		goto out;
	}


	if (arch_irqs_disabled_flags(flags))
		halt();
	else
		safe_halt();

out:
	cpumask_clear_cpu(cpu, &waiting_cpus);
	w->lock = NULL;
	local_irq_restore(flags);
	spin_time_accum_blocked(start);
}
