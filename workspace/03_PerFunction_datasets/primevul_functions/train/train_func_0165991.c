finish_stop(int stop_count)
{


	if (tracehook_notify_jctl(stop_count == 0, CLD_STOPPED)) {
		read_lock(&tasklist_lock);
		do_notify_parent_cldstop(current, CLD_STOPPED);
		read_unlock(&tasklist_lock);
	}

	do {
		schedule();
	} while (try_to_freeze());


	current->exit_code = 0;
}
