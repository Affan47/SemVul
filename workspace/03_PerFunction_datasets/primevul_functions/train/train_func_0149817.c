setup_syscalls_segments(struct x86_emulate_ctxt *ctxt,
	struct kvm_segment *cs, struct kvm_segment *ss)
{
	memset(cs, 0, sizeof(struct kvm_segment));
	kvm_x86_ops->get_segment(ctxt->vcpu, cs, VCPU_SREG_CS);
	memset(ss, 0, sizeof(struct kvm_segment));

	cs->l = 0;
	cs->base = 0;
	cs->g = 1;
	cs->limit = 0xffffffff;
	cs->type = 0x0b;
	cs->s = 1;
	cs->dpl = 0;
	cs->present = 1;
	cs->db = 1;

	ss->unusable = 0;
	ss->base = 0;
	ss->limit = 0xffffffff;
	ss->g = 1;
	ss->s = 1;
	ss->type = 0x03;
	ss->db = 1;
	ss->dpl = 0;
	ss->present = 1;
}
