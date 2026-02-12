static void toggle_interruptibility(struct x86_emulate_ctxt *ctxt, u32 mask)
{
	u32 int_shadow = kvm_x86_ops->get_interrupt_shadow(ctxt->vcpu, mask);


	if (!(int_shadow & mask))
		ctxt->interruptibility = mask;
}
