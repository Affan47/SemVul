static int nested_vmx_run(struct kvm_vcpu *vcpu, bool launch)
{
	struct vmcs12 *vmcs12;
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	u32 interrupt_shadow = vmx_get_interrupt_shadow(vcpu);
	int ret;

	if (!nested_vmx_check_permission(vcpu))
		return 1;

	if (!nested_vmx_handle_enlightened_vmptrld(vcpu, true))
		return 1;

	if (!vmx->nested.hv_evmcs && vmx->nested.current_vmptr == -1ull)
		return nested_vmx_failInvalid(vcpu);

	vmcs12 = get_vmcs12(vcpu);


	if (vmcs12->hdr.shadow_vmcs)
		return nested_vmx_failInvalid(vcpu);

	if (vmx->nested.hv_evmcs) {
		copy_enlightened_to_vmcs12(vmx);

		vmcs12->launch_state = !launch;
	} else if (enable_shadow_vmcs) {
		copy_shadow_to_vmcs12(vmx);
	}


	if (interrupt_shadow & KVM_X86_SHADOW_INT_MOV_SS)
		return nested_vmx_failValid(vcpu,
			VMXERR_ENTRY_EVENTS_BLOCKED_BY_MOV_SS);

	if (vmcs12->launch_state == launch)
		return nested_vmx_failValid(vcpu,
			launch ? VMXERR_VMLAUNCH_NONCLEAR_VMCS
			       : VMXERR_VMRESUME_NONLAUNCHED_VMCS);

	ret = nested_vmx_check_vmentry_prereqs(vcpu, vmcs12);
	if (ret)
		return nested_vmx_failValid(vcpu, ret);


	vmx->nested.nested_run_pending = 1;
	ret = nested_vmx_enter_non_root_mode(vcpu, true);
	vmx->nested.nested_run_pending = !ret;
	if (ret > 0)
		return 1;
	else if (ret)
		return nested_vmx_failValid(vcpu,
			VMXERR_ENTRY_INVALID_CONTROL_FIELD);


	vmx->vcpu.arch.l1tf_flush_l1d = true;


	nested_cache_shadow_vmcs12(vcpu, vmcs12);


	if ((vmcs12->guest_activity_state == GUEST_ACTIVITY_HLT) &&
	    !(vmcs12->vm_entry_intr_info_field & INTR_INFO_VALID_MASK) &&
	    !(vmcs12->cpu_based_vm_exec_control & CPU_BASED_VIRTUAL_NMI_PENDING) &&
	    !((vmcs12->cpu_based_vm_exec_control & CPU_BASED_VIRTUAL_INTR_PENDING) &&
	      (vmcs12->guest_rflags & X86_EFLAGS_IF))) {
		vmx->nested.nested_run_pending = 0;
		return kvm_vcpu_halt(vcpu);
	}
	return 1;
}
