deliver()
{
	struct dst *dst;
	pid_t pid;
	int fds[2];

	var.active = 0;
	var.notdone = 0;

	jl_foreach(conf.dsts, dst) {
		if(dst->disabled_until > time(NULL))
			continue;
		if(dst->disabled_until) {
			dst->disabled_until = 0;
			syslog(conf.facility|LOG_CRIT, "destination %s reenabled", dst->url);
		}
		if(!dst->pid) {
			if(dst->logid == 0) {
				if(dst->log->len) {
					dst->logid = log_first_id(dst->log);
				}
			}
			if(log_find(dst->log, dst->logid) == NULL) {

				continue;
			}

			dst_nonce(dst);
			if(pipe(fds)) {
				syslog(conf.facility|LOG_ERR, "pipe(): failed to create pipe fds");
				continue;
			}
			pid = fork();
			if(pid == 0) {
				close(fds[0]);
				_exit(dst_log(dst, dst->log));
			}
			close(fds[1]);
			if(pid == -1) {
				close(fds[0]);
				syslog(conf.facility|LOG_ERR, "fork(): failed to create delivery process");
			}
			if( pid != -1) {
				dst->pid = pid;
				dst->pipefd = fds[0];
			}
		}
	}

	return 0;
}
