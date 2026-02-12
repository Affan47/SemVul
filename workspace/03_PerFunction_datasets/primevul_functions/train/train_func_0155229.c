static void walk_shadow_page_lockless_begin(struct kvm_vcpu *vcpu)
{
	if (is_tdp_mmu(vcpu->arch.mmu)) {
		kvm_tdp_mmu_walk_lockless_begin();
	} else {


		local_irq_disable();


		smp_store_mb(vcpu->mode, READING_SHADOW_PAGE_TABLES);
	}
}
