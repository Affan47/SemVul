static bool nested_vmcb_valid_sregs(struct kvm_vcpu *vcpu,
				    struct vmcb_save_area *save)
{


	if (CC(!(save->efer & EFER_SVME)))
		return false;

	if (CC((save->cr0 & X86_CR0_CD) == 0 && (save->cr0 & X86_CR0_NW)) ||
	    CC(save->cr0 & ~0xffffffffULL))
		return false;

	if (CC(!kvm_dr6_valid(save->dr6)) || CC(!kvm_dr7_valid(save->dr7)))
		return false;

	if (!nested_vmcb_check_cr3_cr4(vcpu, save))
		return false;

	if (CC(!kvm_valid_efer(vcpu, save->efer)))
		return false;

	return true;
}
