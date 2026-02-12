int compat_restore_altstack(const compat_stack_t __user *uss)
{
	int err = do_compat_sigaltstack(uss, NULL);

	return err == -EFAULT ? err : 0;
}
