fast_pf_fix_direct_spte(struct kvm_vcpu *vcpu, struct kvm_page_fault *fault,
			u64 *sptep, u64 old_spte, u64 new_spte)
{


	if (cmpxchg64(sptep, old_spte, new_spte) != old_spte)
		return false;

	if (is_writable_pte(new_spte) && !is_writable_pte(old_spte))
		mark_page_dirty_in_slot(vcpu->kvm, fault->slot, fault->gfn);

	return true;
}
