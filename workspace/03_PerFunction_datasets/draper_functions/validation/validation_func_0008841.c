rcu_cpu_notify(struct notifier_block *self,
		   unsigned long action, void *hcpu)
{
	long cpu = (long)hcpu;
	struct rcu_data *rdp = per_cpu_ptr(rcu_state_p->rda, cpu);
	struct rcu_node *rnp = rdp->mynode;
	struct rcu_state *rsp;

	switch (action) {
	case CPU_UP_PREPARE:
	case CPU_UP_PREPARE_FROZEN:
		rcu_prepare_cpu(cpu);
		rcu_prepare_kthreads(cpu);
		rcu_spawn_all_nocb_kthreads(cpu);
		break;
	case CPU_ONLINE:
	case CPU_DOWN_FAILED:
		sync_sched_exp_online_cleanup(cpu);
		rcu_boost_kthread_setaffinity(rnp, -1);
		break;
	case CPU_DOWN_PREPARE:
		rcu_boost_kthread_setaffinity(rnp, cpu);
		break;
	case CPU_DYING:
	case CPU_DYING_FROZEN:
		for_each_rcu_flavor(rsp)
			rcu_cleanup_dying_cpu(rsp);
		break;
	case CPU_DYING_IDLE:

		preempt_disable();
		rcu_report_exp_rdp(&rcu_sched_state,
				   this_cpu_ptr(rcu_sched_state.rda), true);
		preempt_enable();

		for_each_rcu_flavor(rsp) {
			rcu_cleanup_dying_idle_cpu(cpu, rsp);
		}
		break;
	case CPU_DEAD:
	case CPU_DEAD_FROZEN:
	case CPU_UP_CANCELED:
	case CPU_UP_CANCELED_FROZEN:
		for_each_rcu_flavor(rsp) {
			rcu_cleanup_dead_cpu(cpu, rsp);
			do_nocb_deferred_wakeup(per_cpu_ptr(rsp->rda, cpu));
		}
		break;
	default:
		break;
	}
	return NOTIFY_OK;
}
