static void direct_pte_prefetch(struct kvm_vcpu *vcpu, u64 *sptep)
{
	struct kvm_mmu_page *sp;

	sp = sptep_to_sp(sptep);


	if (sp_ad_disabled(sp))
		return;

	if (sp->role.level > PG_LEVEL_4K)
		return;


	if (unlikely(vcpu->kvm->mmu_notifier_count))
		return;

	__direct_pte_prefetch(vcpu, sp, sptep);
}
