static void kvm_load_guest_fpu(struct kvm_vcpu *vcpu)
{
	preempt_disable();
	copy_fpregs_to_fpstate(&vcpu->arch.user_fpu);

	__copy_kernel_to_fpregs(&vcpu->arch.guest_fpu.state,
				~XFEATURE_MASK_PKRU);
	preempt_enable();
	trace_kvm_fpu(1);
}
