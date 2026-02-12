int kvm_s390_vcpu_store_status(struct kvm_vcpu *vcpu, unsigned long addr)
{


	save_fpu_regs();
	vcpu->run->s.regs.fpc = current->thread.fpu.fpc;
	save_access_regs(vcpu->run->s.regs.acrs);

	return kvm_s390_store_status_unloaded(vcpu, addr);
}
