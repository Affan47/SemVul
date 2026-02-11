thread_stack_init_shape(struct thread_element *te, const void *sp)
{
	te->stack_base = vmm_page_start(sp);
	te->stack_highest = sp;

	if (thread_sp_direction < 0) {
		te->stack_base = const_ptr_add_offset(te->stack_base,
			compat_pagesize() - sizeof(void *));
	}
}
