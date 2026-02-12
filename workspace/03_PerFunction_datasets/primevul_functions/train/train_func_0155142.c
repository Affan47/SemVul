static bool is_obsolete_root(struct kvm *kvm, hpa_t root_hpa)
{
	struct kvm_mmu_page *sp;

	if (!VALID_PAGE(root_hpa))
		return false;


	sp = to_shadow_page(root_hpa);
	return !sp || is_obsolete_sp(kvm, sp);
}
