static int is_trap_at_addr(struct mm_struct *mm, unsigned long vaddr)
{
	struct page *page;
	uprobe_opcode_t opcode;
	int result;

	pagefault_disable();
	result = __get_user(opcode, (uprobe_opcode_t __user *)vaddr);
	pagefault_enable();

	if (likely(result == 0))
		goto out;


	result = get_user_pages_remote(NULL, mm, vaddr, 1, FOLL_FORCE, &page,
			NULL, NULL);
	if (result < 0)
		return result;

	copy_from_page(page, vaddr, &opcode, UPROBE_SWBP_INSN_SIZE);
	put_page(page);
 out:

	return is_trap_insn(&opcode);
}
