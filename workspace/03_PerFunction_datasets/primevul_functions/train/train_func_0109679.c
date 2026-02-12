static int verify_opcode(struct page *page, unsigned long vaddr, uprobe_opcode_t *new_opcode)
{
	uprobe_opcode_t old_opcode;
	bool is_swbp;


	copy_from_page(page, vaddr, &old_opcode, UPROBE_SWBP_INSN_SIZE);
	is_swbp = is_swbp_insn(&old_opcode);

	if (is_swbp_insn(new_opcode)) {
		if (is_swbp)
			return 0;
	} else {
		if (!is_swbp)
			return 0;
	}

	return 1;
}
