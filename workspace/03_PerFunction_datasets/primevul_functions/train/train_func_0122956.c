static int skip_emulated_instruction(struct kvm_vcpu *vcpu)
{
	unsigned long rip, orig_rip;


	if (!static_cpu_has(X86_FEATURE_HYPERVISOR) ||
	    to_vmx(vcpu)->exit_reason.basic != EXIT_REASON_EPT_MISCONFIG) {
		orig_rip = kvm_rip_read(vcpu);
		rip = orig_rip + vmcs_read32(VM_EXIT_INSTRUCTION_LEN);
#ifdef CONFIG_X86_64


		if (unlikely(((rip ^ orig_rip) >> 31) == 3) && !is_64_bit_mode(vcpu))
			rip = (u32)rip;
#endif
		kvm_rip_write(vcpu, rip);
	} else {
		if (!kvm_emulate_instruction(vcpu, EMULTYPE_SKIP))
			return 0;
	}


	vmx_set_interrupt_shadow(vcpu, 0);

	return 1;
}
