padata_get_next(struct parallel_data *pd)
{
	int cpu, num_cpus;
	unsigned int next_nr, next_index;
	struct padata_parallel_queue *next_queue;
	struct padata_priv *padata;
	struct padata_list *reorder;

	num_cpus = cpumask_weight(pd->cpumask.pcpu);


	next_nr = pd->processed;
	next_index = next_nr % num_cpus;
	cpu = padata_index_to_cpu(pd, next_index);
	next_queue = per_cpu_ptr(pd->pqueue, cpu);

	padata = NULL;

	reorder = &next_queue->reorder;

	spin_lock(&reorder->lock);
	if (!list_empty(&reorder->list)) {
		padata = list_entry(reorder->list.next,
				    struct padata_priv, list);

		list_del_init(&padata->list);
		atomic_dec(&pd->reorder_objects);

		pd->processed++;

		spin_unlock(&reorder->lock);
		goto out;
	}
	spin_unlock(&reorder->lock);

	if (__this_cpu_read(pd->pqueue->cpu_index) == next_queue->cpu_index) {
		padata = ERR_PTR(-ENODATA);
		goto out;
	}

	padata = ERR_PTR(-EINPROGRESS);
out:
	return padata;
}
