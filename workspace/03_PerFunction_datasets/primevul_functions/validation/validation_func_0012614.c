static bool sig_ignored(struct task_struct *t, int sig, bool force)
{


	if (sigismember(&t->blocked, sig) || sigismember(&t->real_blocked, sig))
		return false;


	if (t->ptrace && sig != SIGKILL)
		return false;

	return sig_task_ignored(t, sig, force);
}
