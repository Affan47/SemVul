static void kvm_zap_obsolete_pages(struct kvm *kvm)
{
	struct kvm_mmu_page *sp, *node;
	int nr_zapped, batch = 0;
	bool unstable;

restart:
	list_for_each_entry_safe_reverse(sp, node,
	      &kvm->arch.active_mmu_pages, link) {


		if (!is_obsolete_sp(kvm, sp))
			break;


		if (WARN_ON(sp->role.invalid))
			continue;


		if (batch >= BATCH_ZAP_PAGES &&
		    cond_resched_rwlock_write(&kvm->mmu_lock)) {
			batch = 0;
			goto restart;
		}

		unstable = __kvm_mmu_prepare_zap_page(kvm, sp,
				&kvm->arch.zapped_obsolete_pages, &nr_zapped);
		batch += nr_zapped;

		if (unstable)
			goto restart;
	}


	kvm_mmu_commit_zap_page(kvm, &kvm->arch.zapped_obsolete_pages);
}
