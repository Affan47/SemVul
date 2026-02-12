ia32_setup_arg_pages (struct linux_binprm *bprm, int executable_stack)
{
	int ret;

	ret = setup_arg_pages(bprm, IA32_STACK_TOP, executable_stack);
	if (!ret) {


		current->thread.ppl = ia32_init_pp_list();
	}

	return ret;
}
