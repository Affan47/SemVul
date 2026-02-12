static void handle_swbp(struct pt_regs *regs)
{
	struct uprobe *uprobe;
	unsigned long bp_vaddr;
	int uninitialized_var(is_swbp);

	bp_vaddr = uprobe_get_swbp_addr(regs);
	if (bp_vaddr == get_trampoline_vaddr())
		return handle_trampoline(regs);

	uprobe = find_active_uprobe(bp_vaddr, &is_swbp);
	if (!uprobe) {
		if (is_swbp > 0) {

			send_sig(SIGTRAP, current, 0);
		} else {


			instruction_pointer_set(regs, bp_vaddr);
		}
		return;
	}


	instruction_pointer_set(regs, bp_vaddr);


	smp_rmb();
	if (unlikely(!test_bit(UPROBE_COPY_INSN, &uprobe->flags)))
		goto out;


	if (!get_utask())
		goto out;

	if (arch_uprobe_ignore(&uprobe->arch, regs))
		goto out;

	handler_chain(uprobe, regs);

	if (arch_uprobe_skip_sstep(&uprobe->arch, regs))
		goto out;

	if (!pre_ssout(uprobe, regs, bp_vaddr))
		return;


out:
	put_uprobe(uprobe);
}
