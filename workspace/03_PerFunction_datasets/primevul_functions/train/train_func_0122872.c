static void vmx_set_apic_access_page_addr(struct kvm_vcpu *vcpu)
{
	struct page *page;


	if (is_guest_mode(vcpu)) {
		to_vmx(vcpu)->nested.reload_vmcs01_apic_access_page = true;
		return;
	}

	if (!(secondary_exec_controls_get(to_vmx(vcpu)) &
	    SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES))
		return;

	page = gfn_to_page(vcpu->kvm, APIC_DEFAULT_PHYS_BASE >> PAGE_SHIFT);
	if (is_error_page(page))
		return;

	vmcs_write64(APIC_ACCESS_ADDR, page_to_phys(page));
	vmx_flush_tlb_current(vcpu);


	put_page(page);
}
