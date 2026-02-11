init_per_cpu_tunables(void)
{
	int cpu;
	struct bau_control *bcp;

	for_each_present_cpu(cpu) {
		bcp = &per_cpu(bau_control, cpu);
		bcp->baudisabled		= 0;
		if (nobau)
			bcp->nobau		= 1;
		bcp->statp			= &per_cpu(ptcstats, cpu);

		bcp->timeout_interval		= usec_2_cycles(2*timeout_us);
		bcp->max_concurr		= max_concurr;
		bcp->max_concurr_const		= max_concurr;
		bcp->plugged_delay		= plugged_delay;
		bcp->plugsb4reset		= plugsb4reset;
		bcp->timeoutsb4reset		= timeoutsb4reset;
		bcp->ipi_reset_limit		= ipi_reset_limit;
		bcp->complete_threshold		= complete_threshold;
		bcp->cong_response_us		= congested_respns_us;
		bcp->cong_reps			= congested_reps;
		bcp->disabled_period =		sec_2_cycles(disabled_period);
		bcp->giveup_limit =		giveup_limit;
		spin_lock_init(&bcp->queue_lock);
		spin_lock_init(&bcp->uvhub_lock);
		spin_lock_init(&bcp->disable_lock);
	}
}
