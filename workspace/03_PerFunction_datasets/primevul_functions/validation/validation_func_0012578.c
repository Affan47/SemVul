int send_sig_info(int sig, struct kernel_siginfo *info, struct task_struct *p)
{


	if (!valid_signal(sig))
		return -EINVAL;

	return do_send_sig_info(sig, info, p, PIDTYPE_PID);
}
