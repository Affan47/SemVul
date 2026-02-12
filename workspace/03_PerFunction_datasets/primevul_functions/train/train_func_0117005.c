static int nested_vmx_check_vmentry_hw(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	unsigned long cr3, cr4;
	bool vm_fail;

	if (!nested_early_check)
		return 0;

	if (vmx->msr_autoload.host.nr)
		vmcs_write32(VM_EXIT_MSR_LOAD_COUNT, 0);
	if (vmx->msr_autoload.guest.nr)
		vmcs_write32(VM_ENTRY_MSR_LOAD_COUNT, 0);

	preempt_disable();

	vmx_prepare_switch_to_guest(vcpu);


	vmcs_writel(GUEST_RFLAGS, 0);

	cr3 = __get_current_cr3_fast();
	if (unlikely(cr3 != vmx->loaded_vmcs->host_state.cr3)) {
		vmcs_writel(HOST_CR3, cr3);
		vmx->loaded_vmcs->host_state.cr3 = cr3;
	}

	cr4 = cr4_read_shadow();
	if (unlikely(cr4 != vmx->loaded_vmcs->host_state.cr4)) {
		vmcs_writel(HOST_CR4, cr4);
		vmx->loaded_vmcs->host_state.cr4 = cr4;
	}

	asm(
		"sub $%c[wordsize], %%" _ASM_SP "\n\t"
		"cmp %%" _ASM_SP ", %c[host_state_rsp](%[loaded_vmcs]) \n\t"
		"je 1f \n\t"
		__ex("vmwrite %%" _ASM_SP ", %[HOST_RSP]") "\n\t"
		"mov %%" _ASM_SP ", %c[host_state_rsp](%[loaded_vmcs]) \n\t"
		"1: \n\t"
		"add $%c[wordsize], %%" _ASM_SP "\n\t"


		"cmpb $0, %c[launched](%[loaded_vmcs])\n\t"


		"call vmx_vmenter\n\t"

		CC_SET(be)
	      : ASM_CALL_CONSTRAINT, CC_OUT(be) (vm_fail)
	      :	[HOST_RSP]"r"((unsigned long)HOST_RSP),
		[loaded_vmcs]"r"(vmx->loaded_vmcs),
		[launched]"i"(offsetof(struct loaded_vmcs, launched)),
		[host_state_rsp]"i"(offsetof(struct loaded_vmcs, host_state.rsp)),
		[wordsize]"i"(sizeof(ulong))
	      : "cc", "memory"
	);

	preempt_enable();

	if (vmx->msr_autoload.host.nr)
		vmcs_write32(VM_EXIT_MSR_LOAD_COUNT, vmx->msr_autoload.host.nr);
	if (vmx->msr_autoload.guest.nr)
		vmcs_write32(VM_ENTRY_MSR_LOAD_COUNT, vmx->msr_autoload.guest.nr);

	if (vm_fail) {
		WARN_ON_ONCE(vmcs_read32(VM_INSTRUCTION_ERROR) !=
			     VMXERR_ENTRY_INVALID_CONTROL_FIELD);
		return 1;
	}


	local_irq_enable();
	if (hw_breakpoint_active())
		set_debugreg(__this_cpu_read(cpu_dr7), 7);


	WARN_ON(!(vmcs_read32(VM_EXIT_REASON) &
		VMX_EXIT_REASONS_FAILED_VMENTRY));

	return 0;
}
