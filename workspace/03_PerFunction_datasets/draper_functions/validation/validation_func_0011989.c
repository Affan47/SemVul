prepare_stdio (slurmd_job_t *job, slurmd_task_info_t *task)
{
#ifdef HAVE_PTY_H
	if (job->pty && (task->gtid == 0)) {
		if (login_tty(task->stdin_fd))
			error("login_tty: %m");
		else
			debug3("login_tty good");
		return;
	}
#endif
	io_dup_stdio(task);
	return;
}
