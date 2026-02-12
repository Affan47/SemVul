void vmx_update_cpu_dirty_logging(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);

	if (is_guest_mode(vcpu)) {
		vmx->nested.update_vmcs01_cpu_dirty_logging = true;
		return;
	}


	if (vcpu->kvm->arch.cpu_dirty_logging_count)
		secondary_exec_controls_setbit(vmx, SECONDARY_EXEC_ENABLE_PML);
	else
		secondary_exec_controls_clearbit(vmx, SECONDARY_EXEC_ENABLE_PML);
}
