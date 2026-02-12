static int vmx_smi_allowed(struct kvm_vcpu *vcpu, bool for_injection)
{

	if (to_vmx(vcpu)->nested.nested_run_pending)
		return -EBUSY;
	return !is_smm(vcpu);
}
