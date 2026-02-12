int do_huge_pmd_numa_page(struct vm_fault *vmf, pmd_t pmd)
{
	struct vm_area_struct *vma = vmf->vma;
	struct anon_vma *anon_vma = NULL;
	struct page *page;
	unsigned long haddr = vmf->address & HPAGE_PMD_MASK;
	int page_nid = -1, this_nid = numa_node_id();
	int target_nid, last_cpupid = -1;
	bool page_locked;
	bool migrated = false;
	bool was_writable;
	int flags = 0;

	vmf->ptl = pmd_lock(vma->vm_mm, vmf->pmd);
	if (unlikely(!pmd_same(pmd, *vmf->pmd)))
		goto out_unlock;


	if (unlikely(pmd_trans_migrating(*vmf->pmd))) {
		page = pmd_page(*vmf->pmd);
		if (!get_page_unless_zero(page))
			goto out_unlock;
		spin_unlock(vmf->ptl);
		wait_on_page_locked(page);
		put_page(page);
		goto out;
	}

	page = pmd_page(pmd);
	BUG_ON(is_huge_zero_page(page));
	page_nid = page_to_nid(page);
	last_cpupid = page_cpupid_last(page);
	count_vm_numa_event(NUMA_HINT_FAULTS);
	if (page_nid == this_nid) {
		count_vm_numa_event(NUMA_HINT_FAULTS_LOCAL);
		flags |= TNF_FAULT_LOCAL;
	}


	if (!pmd_savedwrite(pmd))
		flags |= TNF_NO_GROUP;


	page_locked = trylock_page(page);
	target_nid = mpol_misplaced(page, vma, haddr);
	if (target_nid == -1) {

		if (page_locked)
			goto clear_pmdnuma;
	}


	if (!page_locked) {
		page_nid = -1;
		if (!get_page_unless_zero(page))
			goto out_unlock;
		spin_unlock(vmf->ptl);
		wait_on_page_locked(page);
		put_page(page);
		goto out;
	}


	get_page(page);
	spin_unlock(vmf->ptl);
	anon_vma = page_lock_anon_vma_read(page);


	spin_lock(vmf->ptl);
	if (unlikely(!pmd_same(pmd, *vmf->pmd))) {
		unlock_page(page);
		put_page(page);
		page_nid = -1;
		goto out_unlock;
	}


	if (unlikely(!anon_vma)) {
		put_page(page);
		page_nid = -1;
		goto clear_pmdnuma;
	}


	if (mm_tlb_flush_pending(vma->vm_mm))
		flush_tlb_range(vma, haddr, haddr + HPAGE_PMD_SIZE);


	spin_unlock(vmf->ptl);

	migrated = migrate_misplaced_transhuge_page(vma->vm_mm, vma,
				vmf->pmd, pmd, vmf->address, page, target_nid);
	if (migrated) {
		flags |= TNF_MIGRATED;
		page_nid = target_nid;
	} else
		flags |= TNF_MIGRATE_FAIL;

	goto out;
clear_pmdnuma:
	BUG_ON(!PageLocked(page));
	was_writable = pmd_savedwrite(pmd);
	pmd = pmd_modify(pmd, vma->vm_page_prot);
	pmd = pmd_mkyoung(pmd);
	if (was_writable)
		pmd = pmd_mkwrite(pmd);
	set_pmd_at(vma->vm_mm, haddr, vmf->pmd, pmd);
	update_mmu_cache_pmd(vma, vmf->address, vmf->pmd);
	unlock_page(page);
out_unlock:
	spin_unlock(vmf->ptl);

out:
	if (anon_vma)
		page_unlock_anon_vma_read(anon_vma);

	if (page_nid != -1)
		task_numa_fault(last_cpupid, page_nid, HPAGE_PMD_NR,
				flags);

	return 0;
}
