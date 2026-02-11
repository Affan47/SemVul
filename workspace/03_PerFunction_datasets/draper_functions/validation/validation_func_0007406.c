acf_mailbox_exists(struct ast_channel *chan, const char *cmd, char *args, char *buf, size_t len)
{
	struct ast_vm_user svm;
	AST_DECLARE_APP_ARGS(arg,
		AST_APP_ARG(mbox);
		AST_APP_ARG(context);
	);
	static int dep_warning = 0;

	AST_NONSTANDARD_APP_ARGS(arg, args, '@');

	if (ast_strlen_zero(arg.mbox)) {
		ast_log(LOG_ERROR, "MAILBOX_EXISTS requires an argument (<mailbox>[@<context>])\n");
		return -1;
	}

	if (!dep_warning) {
		dep_warning = 1;
		ast_log(AST_LOG_WARNING, "MAILBOX_EXISTS is deprecated.  Please use ${VM_INFO(%s,exists)} instead.\n", args);
	}

	ast_copy_string(buf, find_user(&svm, ast_strlen_zero(arg.context) ? "default" : arg.context, arg.mbox) ? "1" : "0", len);
	return 0;
}
