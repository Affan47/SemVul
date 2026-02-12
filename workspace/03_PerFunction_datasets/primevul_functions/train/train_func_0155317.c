static void kvm_mmu_zap_all_fast(struct kvm *kvm)
{
	lockdep_assert_held(&kvm->slots_lock);

	write_lock(&kvm->mmu_lock);
	trace_kvm_mmu_zap_all_fast(kvm);


	kvm->arch.mmu_valid_gen = kvm->arch.mmu_valid_gen ? 0 : 1;


	if (is_tdp_mmu_enabled(kvm))
		kvm_tdp_mmu_invalidate_all_roots(kvm);


	kvm_make_all_cpus_request(kvm, KVM_REQ_MMU_FREE_OBSOLETE_ROOTS);

	kvm_zap_obsolete_pages(kvm);

	write_unlock(&kvm->mmu_lock);


	if (is_tdp_mmu_enabled(kvm))
		kvm_tdp_mmu_zap_invalidated_roots(kvm);
}
