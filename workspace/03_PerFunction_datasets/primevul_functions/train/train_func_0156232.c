static bool svm_need_emulation_on_page_fault(struct kvm_vcpu *vcpu)
{
	unsigned long cr4 = kvm_read_cr4(vcpu);
	bool smep = cr4 & X86_CR4_SMEP;
	bool smap = cr4 & X86_CR4_SMAP;
	bool is_user = svm_get_cpl(vcpu) == 3;


	if (!kvm_vcpu_gfn_to_memslot(vcpu, kvm_rip_read(vcpu) >> PAGE_SHIFT))
		return true;


	if (smap && (!smep || is_user)) {
		if (!sev_guest(vcpu->kvm))
			return true;

		pr_err_ratelimited("KVM: SEV Guest triggered AMD Erratum 1096\n");
		kvm_make_request(KVM_REQ_TRIPLE_FAULT, vcpu);
	}

	return false;
}
