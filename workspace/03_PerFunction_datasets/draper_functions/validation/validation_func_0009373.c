slurmdb_pack_step_rec(slurmdb_step_rec_t *step,
				  uint16_t rpc_version, Buf buffer)
{
	if(rpc_version >= 5) {
		pack32(step->elapsed, buffer);
		pack_time(step->end, buffer);
		pack32((uint32_t)step->exitcode, buffer);


		pack32(step->ncpus, buffer);
		pack32(step->nnodes, buffer);
		packstr(step->nodes, buffer);
		pack32(step->ntasks, buffer);
		pack32(step->requid, buffer);
		_pack_slurmdb_stats(&step->stats, rpc_version, buffer);
		pack_time(step->start, buffer);
		pack16(step->state, buffer);
		pack32(step->stepid, buffer);
		packstr(step->stepname, buffer);
		pack32(step->suspended, buffer);
		pack32(step->sys_cpu_sec, buffer);
		pack32(step->sys_cpu_usec, buffer);
		pack16(step->task_dist, buffer);
		pack32(step->tot_cpu_sec, buffer);
		pack32(step->tot_cpu_usec, buffer);
		pack32(step->user_cpu_sec, buffer);
		pack32(step->user_cpu_usec, buffer);
	}
}
