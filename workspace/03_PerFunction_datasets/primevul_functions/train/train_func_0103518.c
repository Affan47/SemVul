void psi_cgroup_free(struct cgroup *cgroup)
{
	if (static_branch_likely(&psi_disabled))
		return;

	cancel_delayed_work_sync(&cgroup->psi.avgs_work);
	free_percpu(cgroup->psi.pcpu);

	WARN_ONCE(cgroup->psi.poll_states, "psi: trigger leak\n");
}
