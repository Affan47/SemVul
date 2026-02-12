static void rtrs_clt_remove_path_from_arr(struct rtrs_clt_path *clt_path)
{
	struct rtrs_clt_sess *clt = clt_path->clt;
	struct rtrs_clt_path *next;
	bool wait_for_grace = false;
	int cpu;

	mutex_lock(&clt->paths_mutex);
	list_del_rcu(&clt_path->s.entry);


	synchronize_rcu();


	clt->paths_num--;


	rcu_read_lock();
	next = list_next_or_null_rr_rcu(&clt->paths_list, &clt_path->s.entry,
					typeof(*next), s.entry);
	rcu_read_unlock();


	for_each_possible_cpu(cpu) {
		struct rtrs_clt_path __rcu **ppcpu_path;

		ppcpu_path = per_cpu_ptr(clt->pcpu_path, cpu);
		if (rcu_dereference_protected(*ppcpu_path,
			lockdep_is_held(&clt->paths_mutex)) != clt_path)


			continue;


		if (xchg_paths(ppcpu_path, clt_path, next))


			wait_for_grace = true;
	}
	if (wait_for_grace)
		synchronize_rcu();

	mutex_unlock(&clt->paths_mutex);
}
