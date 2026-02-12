static int queue_pages_pte_range(pmd_t *pmd, unsigned long addr,
			unsigned long end, struct mm_walk *walk)
{
	struct vm_area_struct *vma = walk->vma;
	struct page *page;
	struct queue_pages *qp = walk->private;
	unsigned long flags = qp->flags;
	int ret;
	bool has_unmovable = false;
	pte_t *pte;
	spinlock_t *ptl;

	ptl = pmd_trans_huge_lock(pmd, vma);
	if (ptl) {
		ret = queue_pages_pmd(pmd, ptl, addr, end, walk);
		if (ret != 2)
			return ret;
	}


	if (pmd_trans_unstable(pmd))
		return 0;

	pte = pte_offset_map_lock(walk->mm, pmd, addr, &ptl);
	for (; addr != end; pte++, addr += PAGE_SIZE) {
		if (!pte_present(*pte))
			continue;
		page = vm_normal_page(vma, addr, *pte);
		if (!page)
			continue;


		if (PageReserved(page))
			continue;
		if (!queue_pages_required(page, qp))
			continue;
		if (flags & (MPOL_MF_MOVE | MPOL_MF_MOVE_ALL)) {

			if (!vma_migratable(vma)) {
				has_unmovable = true;
				break;
			}


			if (migrate_page_add(page, qp->pagelist, flags))
				has_unmovable = true;
		} else
			break;
	}
	pte_unmap_unlock(pte - 1, ptl);
	cond_resched();

	if (has_unmovable)
		return 1;

	return addr != end ? -EIO : 0;
}
