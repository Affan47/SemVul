static int prepare_arg_pages(struct linux_binprm *bprm,
			struct user_arg_ptr argv, struct user_arg_ptr envp)
{
	unsigned long limit, ptr_size;

	bprm->argc = count(argv, MAX_ARG_STRINGS);
	if (bprm->argc < 0)
		return bprm->argc;

	bprm->envc = count(envp, MAX_ARG_STRINGS);
	if (bprm->envc < 0)
		return bprm->envc;


	limit = _STK_LIM / 4 * 3;
	limit = min(limit, bprm->rlim_stack.rlim_cur / 4);


	limit = max_t(unsigned long, limit, ARG_MAX);


	ptr_size = (bprm->argc + bprm->envc) * sizeof(void *);
	if (limit <= ptr_size)
		return -E2BIG;
	limit -= ptr_size;

	bprm->argmin = bprm->p - limit;
	return 0;
}
