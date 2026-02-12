static void kvm_mmu_notifier_change_pte(struct mmu_notifier *mn,
					struct mm_struct *mm,
					unsigned long address,
					pte_t pte)
{
	struct kvm *kvm = mmu_notifier_to_kvm(mn);

	trace_kvm_set_spte_hva(address);


	WARN_ON_ONCE(!kvm->mmu_notifier_count);

	kvm_handle_hva_range(mn, address, address + 1, pte, kvm_set_spte_gfn);
}
