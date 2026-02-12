static void fill_prstatus(struct elf_prstatus *prstatus,
			  struct task_struct *p, long signr)
{
	prstatus->pr_info.si_signo = prstatus->pr_cursig = signr;
	prstatus->pr_sigpend = p->pending.signal.sig[0];
	prstatus->pr_sighold = p->blocked.sig[0];
	prstatus->pr_pid = p->pid;
	prstatus->pr_ppid = p->parent->pid;
	prstatus->pr_pgrp = process_group(p);
	prstatus->pr_sid = process_session(p);
	if (thread_group_leader(p)) {


		cputime_to_timeval(cputime_add(p->utime, p->signal->utime),
				   &prstatus->pr_utime);
		cputime_to_timeval(cputime_add(p->stime, p->signal->stime),
				   &prstatus->pr_stime);
	} else {
		cputime_to_timeval(p->utime, &prstatus->pr_utime);
		cputime_to_timeval(p->stime, &prstatus->pr_stime);
	}
	cputime_to_timeval(p->signal->cutime, &prstatus->pr_cutime);
	cputime_to_timeval(p->signal->cstime, &prstatus->pr_cstime);

	prstatus->pr_exec_fdpic_loadmap = p->mm->context.exec_fdpic_loadmap;
	prstatus->pr_interp_fdpic_loadmap = p->mm->context.interp_fdpic_loadmap;
}
