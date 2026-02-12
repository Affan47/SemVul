static int mmu_first_shadow_root_alloc(struct kvm *kvm)
{
	struct kvm_memslots *slots;
	struct kvm_memory_slot *slot;
	int r = 0, i, bkt;


	if (kvm_shadow_root_allocated(kvm))
		return 0;

	mutex_lock(&kvm->slots_arch_lock);


	if (kvm_shadow_root_allocated(kvm))
		goto out_unlock;


	if (kvm_memslots_have_rmaps(kvm) &&
	    kvm_page_track_write_tracking_enabled(kvm))
		goto out_success;

	for (i = 0; i < KVM_ADDRESS_SPACE_NUM; i++) {
		slots = __kvm_memslots(kvm, i);
		kvm_for_each_memslot(slot, bkt, slots) {


			r = memslot_rmap_alloc(slot, slot->npages);
			if (r)
				goto out_unlock;
			r = kvm_page_track_write_tracking_alloc(slot);
			if (r)
				goto out_unlock;
		}
	}


out_success:
	smp_store_release(&kvm->arch.shadow_root_allocated, true);

out_unlock:
	mutex_unlock(&kvm->slots_arch_lock);
	return r;
}
