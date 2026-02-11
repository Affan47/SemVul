setup_sigcontext(struct sigcontext __user *sc, void __user *fpstate,
		     struct pt_regs *regs, unsigned long mask)
{
	int err = 0;

	put_user_try {

#ifdef CONFIG_X86_32
		put_user_ex(get_user_gs(regs), (unsigned int __user *)&sc->gs);
		put_user_ex(regs->fs, (unsigned int __user *)&sc->fs);
		put_user_ex(regs->es, (unsigned int __user *)&sc->es);
		put_user_ex(regs->ds, (unsigned int __user *)&sc->ds);
#endif

		put_user_ex(regs->di, &sc->di);
		put_user_ex(regs->si, &sc->si);
		put_user_ex(regs->bp, &sc->bp);
		put_user_ex(regs->sp, &sc->sp);
		put_user_ex(regs->bx, &sc->bx);
		put_user_ex(regs->dx, &sc->dx);
		put_user_ex(regs->cx, &sc->cx);
		put_user_ex(regs->ax, &sc->ax);
#ifdef CONFIG_X86_64
		put_user_ex(regs->r8, &sc->r8);
		put_user_ex(regs->r9, &sc->r9);
		put_user_ex(regs->r10, &sc->r10);
		put_user_ex(regs->r11, &sc->r11);
		put_user_ex(regs->r12, &sc->r12);
		put_user_ex(regs->r13, &sc->r13);
		put_user_ex(regs->r14, &sc->r14);
		put_user_ex(regs->r15, &sc->r15);
#endif

		put_user_ex(current->thread.trap_nr, &sc->trapno);
		put_user_ex(current->thread.error_code, &sc->err);
		put_user_ex(regs->ip, &sc->ip);
#ifdef CONFIG_X86_32
		put_user_ex(regs->cs, (unsigned int __user *)&sc->cs);
		put_user_ex(regs->flags, &sc->flags);
		put_user_ex(regs->sp, &sc->sp_at_signal);
		put_user_ex(regs->ss, (unsigned int __user *)&sc->ss);
#else
		put_user_ex(regs->flags, &sc->flags);
		put_user_ex(regs->cs, &sc->cs);
		put_user_ex(0, &sc->gs);
		put_user_ex(0, &sc->fs);
#endif

		put_user_ex(fpstate, &sc->fpstate);


		put_user_ex(mask, &sc->oldmask);
		put_user_ex(current->thread.cr2, &sc->cr2);
	} put_user_catch(err);

	return err;
}
