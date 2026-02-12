static bool is_obsolete_sp(struct kvm *kvm, struct kvm_mmu_page *sp)
{
	if (sp->role.invalid)
		return true;


	return !sp->tdp_mmu_page &&
	       unlikely(sp->mmu_valid_gen != kvm->arch.mmu_valid_gen);
}
