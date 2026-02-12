long follow_hugetlb_page(struct mm_struct *mm, struct vm_area_struct *vma,
			 struct page **pages, struct vm_area_struct **vmas,
			 unsigned long *position, unsigned long *nr_pages,
			 long i, unsigned int flags, int *locked)
{
	unsigned long pfn_offset;
	unsigned long vaddr = *position;
	unsigned long remainder = *nr_pages;
	struct hstate *h = hstate_vma(vma);
	int err = -EFAULT, refs;

	while (vaddr < vma->vm_end && remainder) {
		pte_t *pte;
		spinlock_t *ptl = NULL;
		int absent;
		struct page *page;


		if (fatal_signal_pending(current)) {
			remainder = 0;
			break;
		}


		pte = huge_pte_offset(mm, vaddr & huge_page_mask(h),
				      huge_page_size(h));
		if (pte)
			ptl = huge_pte_lock(h, mm, pte);
		absent = !pte || huge_pte_none(huge_ptep_get(pte));


		if (absent && (flags & FOLL_DUMP) &&
		    !hugetlbfs_pagecache_present(h, vma, vaddr)) {
			if (pte)
				spin_unlock(ptl);
			remainder = 0;
			break;
		}


		if (absent || is_swap_pte(huge_ptep_get(pte)) ||
		    ((flags & FOLL_WRITE) &&
		      !huge_pte_write(huge_ptep_get(pte)))) {
			vm_fault_t ret;
			unsigned int fault_flags = 0;

			if (pte)
				spin_unlock(ptl);
			if (flags & FOLL_WRITE)
				fault_flags |= FAULT_FLAG_WRITE;
			if (locked)
				fault_flags |= FAULT_FLAG_ALLOW_RETRY |
					FAULT_FLAG_KILLABLE;
			if (flags & FOLL_NOWAIT)
				fault_flags |= FAULT_FLAG_ALLOW_RETRY |
					FAULT_FLAG_RETRY_NOWAIT;
			if (flags & FOLL_TRIED) {


				fault_flags |= FAULT_FLAG_TRIED;
			}
			ret = hugetlb_fault(mm, vma, vaddr, fault_flags);
			if (ret & VM_FAULT_ERROR) {
				err = vm_fault_to_errno(ret, flags);
				remainder = 0;
				break;
			}
			if (ret & VM_FAULT_RETRY) {
				if (locked &&
				    !(fault_flags & FAULT_FLAG_RETRY_NOWAIT))
					*locked = 0;
				*nr_pages = 0;


				return i;
			}
			continue;
		}

		pfn_offset = (vaddr & ~huge_page_mask(h)) >> PAGE_SHIFT;
		page = pte_page(huge_ptep_get(pte));


		if (!pages && !vmas && !pfn_offset &&
		    (vaddr + huge_page_size(h) < vma->vm_end) &&
		    (remainder >= pages_per_huge_page(h))) {
			vaddr += huge_page_size(h);
			remainder -= pages_per_huge_page(h);
			i += pages_per_huge_page(h);
			spin_unlock(ptl);
			continue;
		}


		refs = min3(pages_per_huge_page(h) - pfn_offset, remainder,
		    (vma->vm_end - ALIGN_DOWN(vaddr, PAGE_SIZE)) >> PAGE_SHIFT);

		if (pages || vmas)
			record_subpages_vmas(mem_map_offset(page, pfn_offset),
					     vma, refs,
					     likely(pages) ? pages + i : NULL,
					     vmas ? vmas + i : NULL);

		if (pages) {


			if (WARN_ON_ONCE(!try_grab_compound_head(pages[i],
								 refs,
								 flags))) {
				spin_unlock(ptl);
				remainder = 0;
				err = -ENOMEM;
				break;
			}
		}

		vaddr += (refs << PAGE_SHIFT);
		remainder -= refs;
		i += refs;

		spin_unlock(ptl);
	}
	*nr_pages = remainder;


	*position = vaddr;

	return i ? i : err;
}
