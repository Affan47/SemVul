rinoo_sched_loop(t_sched *sched)
{
	sched->stop = false;
	if (rinoo_spawn_start(sched) != 0) {
		goto loop_stop;
	}
	while (!rinoo_sched_end(sched)) {
		rinoo_sched_poll(sched);
	}
loop_stop:
	rinoo_spawn_join(sched);
}
