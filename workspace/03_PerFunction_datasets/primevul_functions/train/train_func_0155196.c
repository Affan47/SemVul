int mmu_try_to_unsync_pages(struct kvm *kvm, const struct kvm_memory_slot *slot,
			    gfn_t gfn, bool can_unsync, bool prefetch)
{
	struct kvm_mmu_page *sp;
	bool locked = false;


	if (kvm_slot_page_track_is_active(kvm, slot, gfn, KVM_PAGE_TRACK_WRITE))
		return -EPERM;


	for_each_gfn_indirect_valid_sp(kvm, sp, gfn) {
		if (!can_unsync)
			return -EPERM;

		if (sp->unsync)
			continue;

		if (prefetch)
			return -EEXIST;


		if (!locked) {
			locked = true;
			spin_lock(&kvm->arch.mmu_unsync_pages_lock);


			if (READ_ONCE(sp->unsync))
				continue;
		}

		WARN_ON(sp->role.level != PG_LEVEL_4K);
		kvm_unsync_page(kvm, sp);
	}
	if (locked)
		spin_unlock(&kvm->arch.mmu_unsync_pages_lock);


	smp_wmb();

	return 0;
}
