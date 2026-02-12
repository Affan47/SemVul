static int copy_siginfo_from_user_any(kernel_siginfo_t *kinfo, siginfo_t *info)
{
#ifdef CONFIG_COMPAT


	if (in_compat_syscall())
		return copy_siginfo_from_user32(
			kinfo, (struct compat_siginfo __user *)info);
#endif
	return copy_siginfo_from_user(kinfo, info);
}
