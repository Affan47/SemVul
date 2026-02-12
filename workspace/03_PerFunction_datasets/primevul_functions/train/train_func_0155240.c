void kvm_mmu_new_pgd(struct kvm_vcpu *vcpu, gpa_t new_pgd)
{
	struct kvm_mmu *mmu = vcpu->arch.mmu;
	union kvm_mmu_page_role new_role = mmu->mmu_role.base;

	if (!fast_pgd_switch(vcpu->kvm, mmu, new_pgd, new_role)) {

		return;
	}


	kvm_make_request(KVM_REQ_LOAD_MMU_PGD, vcpu);

	if (force_flush_and_sync_on_reuse) {
		kvm_make_request(KVM_REQ_MMU_SYNC, vcpu);
		kvm_make_request(KVM_REQ_TLB_FLUSH_CURRENT, vcpu);
	}


	vcpu_clear_mmio_info(vcpu, MMIO_GVA_ANY);


	if (!new_role.direct)
		__clear_sp_write_flooding_count(
				to_shadow_page(vcpu->arch.mmu->root.hpa));
}
