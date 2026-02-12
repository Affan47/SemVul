static void sync_regs(struct kvm_vcpu *vcpu, struct kvm_run *kvm_run)
{
	if (kvm_run->kvm_dirty_regs & KVM_SYNC_PREFIX)
		kvm_s390_set_prefix(vcpu, kvm_run->s.regs.prefix);
	if (kvm_run->kvm_dirty_regs & KVM_SYNC_CRS) {
		memcpy(&vcpu->arch.sie_block->gcr, &kvm_run->s.regs.crs, 128);

		kvm_make_request(KVM_REQ_TLB_FLUSH, vcpu);
	}
	if (kvm_run->kvm_dirty_regs & KVM_SYNC_ARCH0) {
		kvm_s390_set_cpu_timer(vcpu, kvm_run->s.regs.cputm);
		vcpu->arch.sie_block->ckc = kvm_run->s.regs.ckc;
	}
	save_access_regs(vcpu->arch.host_acrs);
	restore_access_regs(vcpu->run->s.regs.acrs);

	save_fpu_regs();
	vcpu->arch.host_fpregs.fpc = current->thread.fpu.fpc;
	vcpu->arch.host_fpregs.regs = current->thread.fpu.regs;
	if (MACHINE_HAS_VX)
		current->thread.fpu.regs = vcpu->run->s.regs.vrs;
	else
		current->thread.fpu.regs = vcpu->run->s.regs.fprs;
	current->thread.fpu.fpc = vcpu->run->s.regs.fpc;
	if (test_fp_ctl(current->thread.fpu.fpc))

		current->thread.fpu.fpc = 0;


	if (likely(!kvm_s390_pv_cpu_is_protected(vcpu))) {
		sync_regs_fmt2(vcpu, kvm_run);
	} else {


		vcpu->arch.sie_block->gpsw.mask &= ~PSW_MASK_CC;
		vcpu->arch.sie_block->gpsw.mask |= kvm_run->psw_mask &
						   PSW_MASK_CC;
	}

	kvm_run->kvm_dirty_regs = 0;
}
