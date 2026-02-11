handle_event( pid_t pid, int status, struct rusage usage )
{
	struct pfs_process *p;
	int signum;

	p = pfs_process_lookup(pid);
	if(!p) {
		debug(D_PROCESS,"killing unexpected pid %d",pid);
		kill(pid,SIGKILL);
		return;
	}

	if(WIFEXITED(status)) {
		debug(D_PROCESS,"pid %d exited normally with code %d",pid,WEXITSTATUS(status));
		pfs_process_stop(p,status,usage);
		if(pid==root_pid) root_exitstatus = status;
	} else if(WIFSIGNALED(status)) {
		signum = WTERMSIG(status);
		debug(D_PROCESS,"pid %d exited abnormally with signal %d (%s)",pid,signum,string_signal(signum));
		pfs_process_stop(p,status,usage);
		if(pid==root_pid) root_exitstatus = status;
	} else if(WIFSTOPPED(status)) {
		signum = WSTOPSIG(status);
		if(signum==SIGTRAP) {
			p->nsyscalls++;
			pfs_dispatch(p,0);
		} else {
			debug(D_PROCESS,"pid %d received signal %d (%s) (state %d)",pid,signum,string_signal(signum),p->state);
			if(signum==SIGTTIN) {
				tcsetpgrp(0,pid);
				tracer_continue(p->tracer,SIGCONT);
			} else if(signum==SIGTTOU) {
				tcsetpgrp(1,pid);
				tcsetpgrp(2,pid);
				tracer_continue(p->tracer,SIGCONT);
			} else {
				tracer_continue(p->tracer,signum);
				if(signum==SIGSTOP && p->nsyscalls==0) {
					kill(p->pid,SIGCONT);
				}
			}
		}
	} else {
		fatal("pid %d stopped with strange status %d",pid,status);
	}
}
