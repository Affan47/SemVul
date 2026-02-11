run_poll_loop()
{
	int next;

	tv_update_date(0,1);
	while (1) {

		signal_process_queue();


		wake_expired_tasks(&next);


		process_runnable_tasks(&next);


		maintain_proxies(&next);


		if (!actconn && listeners == 0)
			break;


		cur_poller.poll(&cur_poller, next);
	}
}
