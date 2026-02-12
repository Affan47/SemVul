void audit_free(struct task_struct *tsk)
{
	struct audit_context *context;

	context = audit_get_context(tsk, 0, 0);
	if (likely(!context))
		return;


	if (context->in_syscall && context->auditable)
		audit_log_exit(context, tsk);

	audit_free_context(context);
}
