signal_mdevs(unsigned my_pid)
{
	procps_status_t* p = NULL;
	while ((p = procps_scan(p, PSSCAN_ARGV0)) != NULL) {
		if (p->pid != my_pid
		 && p->argv0
		 && strcmp(bb_basename(p->argv0), "mdev") == 0
		) {
			kill(p->pid, SIGCHLD);
		}
	}
}
