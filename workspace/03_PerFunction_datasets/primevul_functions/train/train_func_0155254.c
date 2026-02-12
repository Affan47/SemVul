void kvm_mmu_slot_remove_write_access(struct kvm *kvm,
				      const struct kvm_memory_slot *memslot,
				      int start_level)
{
	bool flush = false;

	if (kvm_memslots_have_rmaps(kvm)) {
		write_lock(&kvm->mmu_lock);
		flush = slot_handle_level(kvm, memslot, slot_rmap_write_protect,
					  start_level, KVM_MAX_HUGEPAGE_LEVEL,
					  false);
		write_unlock(&kvm->mmu_lock);
	}

	if (is_tdp_mmu_enabled(kvm)) {
		read_lock(&kvm->mmu_lock);
		flush |= kvm_tdp_mmu_wrprot_slot(kvm, memslot, start_level);
		read_unlock(&kvm->mmu_lock);
	}


	if (flush)
		kvm_arch_flush_remote_tlbs_memslot(kvm, memslot);
}
