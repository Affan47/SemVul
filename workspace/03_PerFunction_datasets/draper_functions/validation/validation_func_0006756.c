setup_singlestep(struct kprobe *p, struct pt_regs *regs,
			     struct kprobe_ctlblk *kcb, int reenter)
{
	if (setup_detour_execution(p, regs, reenter))
		return;

#if !defined(CONFIG_PREEMPT)
	if (p->ainsn.boostable == 1 && !p->post_handler) {

		if (!reenter)
			reset_current_kprobe();


		regs->ip = (unsigned long)p->ainsn.insn;
		preempt_enable_no_resched();
		return;
	}
#endif
	if (reenter) {
		save_previous_kprobe(kcb);
		set_current_kprobe(p, regs, kcb);
		kcb->kprobe_status = KPROBE_REENTER;
	} else
		kcb->kprobe_status = KPROBE_HIT_SS;

	clear_btf();
	regs->flags |= X86_EFLAGS_TF;
	regs->flags &= ~X86_EFLAGS_IF;

	if (p->opcode == BREAKPOINT_INSTRUCTION)
		regs->ip = (unsigned long)p->addr;
	else
		regs->ip = (unsigned long)p->ainsn.insn;
}
