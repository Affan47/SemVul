velocity_disable(struct nic *nic __unused)
{


	struct mac_regs *regs = vptr->mac_regs;
	mac_disable_int(regs);
	writel(CR0_STOP, &regs->CR0Set);
	writew(0xFFFF, &regs->TDCSRClr);
	writeb(0xFF, &regs->RDCSRClr);
	safe_disable_mii_autopoll(regs);
	mac_clear_isr(regs);


	vptr->flags &= (~VELOCITY_FLAGS_OPENED);
}
