no_context(struct pt_regs *regs, unsigned long error_code,
	   unsigned long address, int signal, int si_code)
{
	struct task_struct *tsk = current;
	unsigned long flags;
	int sig;


	if (fixup_exception(regs, X86_TRAP_PF)) {


		if (in_interrupt())
			return;


		if (current->thread.sig_on_uaccess_err && signal) {
			tsk->thread.trap_nr = X86_TRAP_PF;
			tsk->thread.error_code = error_code | X86_PF_USER;
			tsk->thread.cr2 = address;


			force_sig_info_fault(signal, si_code, address,
					     tsk, NULL, 0);
		}


		return;
	}

#ifdef CONFIG_VMAP_STACK


	if (is_vmalloc_addr((void *)address) &&
	    (((unsigned long)tsk->stack - 1 - address < PAGE_SIZE) ||
	     address - ((unsigned long)tsk->stack + THREAD_SIZE) < PAGE_SIZE)) {
		unsigned long stack = this_cpu_read(orig_ist.ist[DOUBLEFAULT_STACK]) - sizeof(void *);


		asm volatile ("movq %[stack], %%rsp\n\t"
			      "call handle_stack_overflow\n\t"
			      "1: jmp 1b"
			      : ASM_CALL_CONSTRAINT
			      : "D" ("kernel stack overflow (page fault)"),
				"S" (regs), "d" (address),
				[stack] "rm" (stack));
		unreachable();
	}
#endif


	if (is_prefetch(regs, error_code, address))
		return;

	if (is_errata93(regs, address))
		return;


	flags = oops_begin();

	show_fault_oops(regs, error_code, address);

	if (task_stack_end_corrupted(tsk))
		printk(KERN_EMERG "Thread overran stack, or stack corrupted\n");

	tsk->thread.cr2		= address;
	tsk->thread.trap_nr	= X86_TRAP_PF;
	tsk->thread.error_code	= error_code;

	sig = SIGKILL;
	if (__die("Oops", regs, error_code))
		sig = 0;


	printk(KERN_DEFAULT "CR2: %016lx\n", address);

	oops_end(flags, regs, sig);
}
