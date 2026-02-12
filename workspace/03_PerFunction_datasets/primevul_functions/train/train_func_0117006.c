static int nested_vmx_failValid(struct kvm_vcpu *vcpu,
				u32 vm_instruction_error)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);


	if (vmx->nested.current_vmptr == -1ull && !vmx->nested.hv_evmcs)
		return nested_vmx_failInvalid(vcpu);

	vmx_set_rflags(vcpu, (vmx_get_rflags(vcpu)
			& ~(X86_EFLAGS_CF | X86_EFLAGS_PF | X86_EFLAGS_AF |
			    X86_EFLAGS_SF | X86_EFLAGS_OF))
			| X86_EFLAGS_ZF);
	get_vmcs12(vcpu)->vm_instruction_error = vm_instruction_error;


	return kvm_skip_emulated_instruction(vcpu);
}
