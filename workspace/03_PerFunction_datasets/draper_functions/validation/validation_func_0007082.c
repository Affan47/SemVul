set_state(struct multi_stop_data *msdata,
		      enum multi_stop_state newstate)
{

	atomic_set(&msdata->thread_ack, msdata->num_threads);
	smp_wmb();
	msdata->state = newstate;
}
