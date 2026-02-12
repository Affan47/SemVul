static int FNAME(fetch)(struct kvm_vcpu *vcpu, struct kvm_page_fault *fault,
			 struct guest_walker *gw)
{
	struct kvm_mmu_page *sp = NULL;
	struct kvm_shadow_walk_iterator it;
	unsigned int direct_access, access;
	int top_level, ret;
	gfn_t base_gfn = fault->gfn;

	WARN_ON_ONCE(gw->gfn != base_gfn);
	direct_access = gw->pte_access;

	top_level = vcpu->arch.mmu->root_level;
	if (top_level == PT32E_ROOT_LEVEL)
		top_level = PT32_ROOT_LEVEL;


	if (FNAME(gpte_changed)(vcpu, gw, top_level))
		goto out_gpte_changed;

	if (WARN_ON(!VALID_PAGE(vcpu->arch.mmu->root.hpa)))
		goto out_gpte_changed;

	for (shadow_walk_init(&it, vcpu, fault->addr);
	     shadow_walk_okay(&it) && it.level > gw->level;
	     shadow_walk_next(&it)) {
		gfn_t table_gfn;

		clear_sp_write_flooding_count(it.sptep);
		drop_large_spte(vcpu, it.sptep);

		sp = NULL;
		if (!is_shadow_present_pte(*it.sptep)) {
			table_gfn = gw->table_gfn[it.level - 2];
			access = gw->pt_access[it.level - 2];
			sp = kvm_mmu_get_page(vcpu, table_gfn, fault->addr,
					      it.level-1, false, access);


			if (sp->unsync_children &&
			    mmu_sync_children(vcpu, sp, false))
				return RET_PF_RETRY;
		}


		if (FNAME(gpte_changed)(vcpu, gw, it.level - 1))
			goto out_gpte_changed;

		if (sp)
			link_shadow_page(vcpu, it.sptep, sp);
	}

	kvm_mmu_hugepage_adjust(vcpu, fault);

	trace_kvm_mmu_spte_requested(fault);

	for (; shadow_walk_okay(&it); shadow_walk_next(&it)) {
		clear_sp_write_flooding_count(it.sptep);


		if (fault->nx_huge_page_workaround_enabled)
			disallowed_hugepage_adjust(fault, *it.sptep, it.level);

		base_gfn = fault->gfn & ~(KVM_PAGES_PER_HPAGE(it.level) - 1);
		if (it.level == fault->goal_level)
			break;

		validate_direct_spte(vcpu, it.sptep, direct_access);

		drop_large_spte(vcpu, it.sptep);

		if (!is_shadow_present_pte(*it.sptep)) {
			sp = kvm_mmu_get_page(vcpu, base_gfn, fault->addr,
					      it.level - 1, true, direct_access);
			link_shadow_page(vcpu, it.sptep, sp);
			if (fault->huge_page_disallowed &&
			    fault->req_level >= it.level)
				account_huge_nx_page(vcpu->kvm, sp);
		}
	}

	if (WARN_ON_ONCE(it.level != fault->goal_level))
		return -EFAULT;

	ret = mmu_set_spte(vcpu, fault->slot, it.sptep, gw->pte_access,
			   base_gfn, fault->pfn, fault);
	if (ret == RET_PF_SPURIOUS)
		return ret;

	FNAME(pte_prefetch)(vcpu, gw, it.sptep);
	++vcpu->stat.pf_fixed;
	return ret;

out_gpte_changed:
	return RET_PF_RETRY;
}
