void fx_init(struct kvm_vcpu *vcpu)
{
	unsigned after_mxcsr_mask;


	if (!used_math())
		kvm_fx_save(&vcpu->arch.host_fx_image);


	preempt_disable();
	kvm_fx_save(&vcpu->arch.host_fx_image);
	kvm_fx_finit();
	kvm_fx_save(&vcpu->arch.guest_fx_image);
	kvm_fx_restore(&vcpu->arch.host_fx_image);
	preempt_enable();

	vcpu->arch.cr0 |= X86_CR0_ET;
	after_mxcsr_mask = offsetof(struct i387_fxsave_struct, st_space);
	vcpu->arch.guest_fx_image.mxcsr = 0x1f80;
	memset((void *)&vcpu->arch.guest_fx_image + after_mxcsr_mask,
	       0, sizeof(struct i387_fxsave_struct) - after_mxcsr_mask);
}
