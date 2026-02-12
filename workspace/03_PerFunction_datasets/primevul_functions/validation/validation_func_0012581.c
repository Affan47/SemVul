int flush_old_exec(struct linux_binprm * bprm)
{
	struct task_struct *me = current;
	int retval;


	retval = de_thread(me);
	if (retval)
		goto out;


	set_mm_exe_file(bprm->mm, bprm->file);


	acct_arg_size(bprm, 0);
	retval = exec_mmap(bprm->mm);
	if (retval)
		goto out;


	bprm->called_exec_mmap = 1;
	bprm->mm = NULL;

#ifdef CONFIG_POSIX_TIMERS
	exit_itimers(me->signal);
	flush_itimer_signals();
#endif


	retval = unshare_sighand(me);
	if (retval)
		goto out;

	set_fs(USER_DS);
	me->flags &= ~(PF_RANDOMIZE | PF_FORKNOEXEC | PF_KTHREAD |
					PF_NOFREEZE | PF_NO_SETAFFINITY);
	flush_thread();
	me->personality &= ~bprm->per_clear;


	do_close_on_exec(me->files);
	return 0;

out:
	return retval;
}
