print_one_rcu_data(struct seq_file *m, struct rcu_data *rdp)
{
	long ql, qll;

	if (!rdp->beenonline)
		return;
	seq_printf(m, "%3d%cc=%ld g=%ld cnq=%d/%d:%d",
		   rdp->cpu,
		   cpu_is_offline(rdp->cpu) ? '!' : ' ',
		   ulong2long(rdp->completed), ulong2long(rdp->gpnum),
		   rdp->cpu_no_qs.b.norm,
		   rdp->rcu_qs_ctr_snap == per_cpu(rcu_qs_ctr, rdp->cpu),
		   rdp->core_needs_qs);
	seq_printf(m, " dt=%d/%llx/%d df=%lu",
		   atomic_read(&rdp->dynticks->dynticks),
		   rdp->dynticks->dynticks_nesting,
		   rdp->dynticks->dynticks_nmi_nesting,
		   rdp->dynticks_fqs);
	seq_printf(m, " of=%lu", rdp->offline_fqs);
	rcu_nocb_q_lengths(rdp, &ql, &qll);
	qll += rdp->qlen_lazy;
	ql += rdp->qlen;
	seq_printf(m, " ql=%ld/%ld qs=%c%c%c%c",
		   qll, ql,
		   ".N"[rdp->nxttail[RCU_NEXT_READY_TAIL] !=
			rdp->nxttail[RCU_NEXT_TAIL]],
		   ".R"[rdp->nxttail[RCU_WAIT_TAIL] !=
			rdp->nxttail[RCU_NEXT_READY_TAIL]],
		   ".W"[rdp->nxttail[RCU_DONE_TAIL] !=
			rdp->nxttail[RCU_WAIT_TAIL]],
		   ".D"[&rdp->nxtlist != rdp->nxttail[RCU_DONE_TAIL]]);
#ifdef CONFIG_RCU_BOOST
	seq_printf(m, " kt=%d/%c ktl=%x",
		   per_cpu(rcu_cpu_has_work, rdp->cpu),
		   convert_kthread_status(per_cpu(rcu_cpu_kthread_status,
					  rdp->cpu)),
		   per_cpu(rcu_cpu_kthread_loops, rdp->cpu) & 0xffff);
#endif
	seq_printf(m, " b=%ld", rdp->blimit);
	seq_printf(m, " ci=%lu nci=%lu co=%lu ca=%lu\n",
		   rdp->n_cbs_invoked, rdp->n_nocbs_invoked,
		   rdp->n_cbs_orphaned, rdp->n_cbs_adopted);
}
