int nested_vmx_enter_non_root_mode(struct kvm_vcpu *vcpu, bool from_vmentry)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	struct vmcs12 *vmcs12 = get_vmcs12(vcpu);
	bool evaluate_pending_interrupts;
	u32 exit_reason = EXIT_REASON_INVALID_STATE;
	u32 exit_qual;

	evaluate_pending_interrupts = vmcs_read32(CPU_BASED_VM_EXEC_CONTROL) &
		(CPU_BASED_VIRTUAL_INTR_PENDING | CPU_BASED_VIRTUAL_NMI_PENDING);
	if (likely(!evaluate_pending_interrupts) && kvm_vcpu_apicv_active(vcpu))
		evaluate_pending_interrupts |= vmx_has_apicv_interrupt(vcpu);

	if (!(vmcs12->vm_entry_controls & VM_ENTRY_LOAD_DEBUG_CONTROLS))
		vmx->nested.vmcs01_debugctl = vmcs_read64(GUEST_IA32_DEBUGCTL);
	if (kvm_mpx_supported() &&
		!(vmcs12->vm_entry_controls & VM_ENTRY_LOAD_BNDCFGS))
		vmx->nested.vmcs01_guest_bndcfgs = vmcs_read64(GUEST_BNDCFGS);

	vmx_switch_vmcs(vcpu, &vmx->nested.vmcs02);

	prepare_vmcs02_early(vmx, vmcs12);

	if (from_vmentry) {
		nested_get_vmcs12_pages(vcpu);

		if (nested_vmx_check_vmentry_hw(vcpu)) {
			vmx_switch_vmcs(vcpu, &vmx->vmcs01);
			return -1;
		}

		if (nested_vmx_check_vmentry_postreqs(vcpu, vmcs12, &exit_qual))
			goto vmentry_fail_vmexit;
	}

	enter_guest_mode(vcpu);
	if (vmcs12->cpu_based_vm_exec_control & CPU_BASED_USE_TSC_OFFSETING)
		vcpu->arch.tsc_offset += vmcs12->tsc_offset;

	if (prepare_vmcs02(vcpu, vmcs12, &exit_qual))
		goto vmentry_fail_vmexit_guest_mode;

	if (from_vmentry) {
		exit_reason = EXIT_REASON_MSR_LOAD_FAIL;
		exit_qual = nested_vmx_load_msr(vcpu,
						vmcs12->vm_entry_msr_load_addr,
						vmcs12->vm_entry_msr_load_count);
		if (exit_qual)
			goto vmentry_fail_vmexit_guest_mode;
	} else {


		kvm_make_request(KVM_REQ_GET_VMCS12_PAGES, vcpu);
	}


	if (unlikely(evaluate_pending_interrupts))
		kvm_make_request(KVM_REQ_EVENT, vcpu);


	vmx->nested.preemption_timer_expired = false;
	if (nested_cpu_has_preemption_timer(vmcs12))
		vmx_start_preemption_timer(vcpu);


	return 0;


vmentry_fail_vmexit_guest_mode:
	if (vmcs12->cpu_based_vm_exec_control & CPU_BASED_USE_TSC_OFFSETING)
		vcpu->arch.tsc_offset -= vmcs12->tsc_offset;
	leave_guest_mode(vcpu);

vmentry_fail_vmexit:
	vmx_switch_vmcs(vcpu, &vmx->vmcs01);

	if (!from_vmentry)
		return 1;

	load_vmcs12_host_state(vcpu, vmcs12);
	vmcs12->vm_exit_reason = exit_reason | VMX_EXIT_REASONS_FAILED_VMENTRY;
	vmcs12->exit_qualification = exit_qual;
	if (enable_shadow_vmcs || vmx->nested.hv_evmcs)
		vmx->nested.need_vmcs12_sync = true;
	return 1;
}
