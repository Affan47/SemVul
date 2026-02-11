_delayed_job_start_time(struct job_record *job_ptr)
{
	uint32_t part_node_cnt, part_cpu_cnt, part_cpus_per_node;
	uint32_t job_size_cpus, job_size_nodes, job_time;
	uint64_t cume_space_time = 0;
	struct job_record *job_q_ptr;
	ListIterator job_iterator;

	if (job_ptr->part_ptr == NULL)
		return;
	part_node_cnt = job_ptr->part_ptr->total_nodes;
	part_cpu_cnt  = job_ptr->part_ptr->total_cpus;
	if (part_node_cnt > part_cpu_cnt)
		part_cpus_per_node = part_node_cnt / part_cpu_cnt;
	else
		part_cpus_per_node = 1;

	job_iterator = list_iterator_create(job_list);
	if (job_iterator == NULL)
		fatal("list_iterator_create memory allocation failure");
	while ((job_q_ptr = (struct job_record *) list_next(job_iterator))) {
		if (!IS_JOB_PENDING(job_q_ptr) || !job_q_ptr->details ||
		    (job_q_ptr->part_ptr != job_ptr->part_ptr) ||
		    (job_q_ptr->priority < job_ptr->priority) ||
		    (job_q_ptr->job_id == job_ptr->job_id))
			continue;
		if (job_q_ptr->details->min_nodes == NO_VAL)
			job_size_nodes = 1;
		else
			job_size_nodes = job_q_ptr->details->min_nodes;
		if (job_q_ptr->details->min_cpus == NO_VAL)
			job_size_cpus = 1;
		else
			job_size_cpus = job_q_ptr->details->min_nodes;
		job_size_cpus = MAX(job_size_cpus,
				    (job_size_nodes * part_cpus_per_node));
		if (job_ptr->time_limit == NO_VAL)
			job_time = job_q_ptr->part_ptr->max_time;
		else
			job_time = job_q_ptr->time_limit;
		cume_space_time += job_size_cpus * job_time;
	}
	list_iterator_destroy(job_iterator);
	cume_space_time /= part_cpu_cnt;
	cume_space_time *= 60;
	debug2("Increasing estimated start of job %u by %"PRIu64" secs",
	       job_ptr->job_id, cume_space_time);
	job_ptr->start_time += cume_space_time;
}
