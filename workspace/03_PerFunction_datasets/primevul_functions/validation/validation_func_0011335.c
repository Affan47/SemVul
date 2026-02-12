static void kvm_arch_vcpu_ioctl_initial_reset(struct kvm_vcpu *vcpu)
{

	kvm_arch_vcpu_ioctl_normal_reset(vcpu);


	vcpu->arch.sie_block->gpsw.mask = 0;
	vcpu->arch.sie_block->gpsw.addr = 0;
	kvm_s390_set_prefix(vcpu, 0);
	kvm_s390_set_cpu_timer(vcpu, 0);
	vcpu->arch.sie_block->ckc = 0;
	memset(vcpu->arch.sie_block->gcr, 0, sizeof(vcpu->arch.sie_block->gcr));
	vcpu->arch.sie_block->gcr[0] = CR0_INITIAL_MASK;
	vcpu->arch.sie_block->gcr[14] = CR14_INITIAL_MASK;
	vcpu->run->s.regs.fpc = 0;


	if (!kvm_s390_pv_cpu_is_protected(vcpu)) {
		vcpu->arch.sie_block->gbea = 1;
		vcpu->arch.sie_block->pp = 0;
		vcpu->arch.sie_block->fpf &= ~FPF_BPBC;
		vcpu->arch.sie_block->todpr = 0;
	}
}
