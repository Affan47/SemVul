arch_ftrace_trampoline_free(struct ftrace_ops *ops)
{
	if (!ops || !(ops->flags & FTRACE_OPS_FL_ALLOC_TRAMP))
		return;

	tramp_free((void *)ops->trampoline);
	ops->trampoline = 0;
}
