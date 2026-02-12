static bool is_page_fault_stale(struct kvm_vcpu *vcpu,
				struct kvm_page_fault *fault, int mmu_seq)
{
	struct kvm_mmu_page *sp = to_shadow_page(vcpu->arch.mmu->root.hpa);


	if (sp && is_obsolete_sp(vcpu->kvm, sp))
		return true;


	if (!sp && kvm_test_request(KVM_REQ_MMU_FREE_OBSOLETE_ROOTS, vcpu))
		return true;

	return fault->slot &&
	       mmu_notifier_retry_hva(vcpu->kvm, mmu_seq, fault->hva);
}
