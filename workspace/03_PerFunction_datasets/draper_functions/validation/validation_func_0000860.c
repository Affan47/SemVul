is_trap_at_addr(struct mm_struct *mm, unsigned long vaddr)
{
	struct page *page;
	uprobe_opcode_t opcode;
	int result;

	pagefault_disable();
	result = __copy_from_user_inatomic(&opcode, (void __user*)vaddr,
							sizeof(opcode));
	pagefault_enable();

	if (likely(result == 0))
		goto out;

	result = get_user_pages(NULL, mm, vaddr, 1, 0, 1, &page, NULL);
	if (result < 0)
		return result;

	copy_from_page(page, vaddr, &opcode, UPROBE_SWBP_INSN_SIZE);
	put_page(page);
 out:

	return is_trap_insn(&opcode);
}
