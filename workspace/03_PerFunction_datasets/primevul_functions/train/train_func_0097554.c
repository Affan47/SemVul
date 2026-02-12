void restore_reserve_on_error(struct hstate *h, struct vm_area_struct *vma,
			unsigned long address, struct page *page)
{
	long rc = vma_needs_reservation(h, vma, address);

	if (HPageRestoreReserve(page)) {
		if (unlikely(rc < 0))


			ClearHPageRestoreReserve(page);
		else if (rc)
			(void)vma_add_reservation(h, vma, address);
		else
			vma_end_reservation(h, vma, address);
	} else {
		if (!rc) {


			rc = vma_del_reservation(h, vma, address);
			if (rc < 0)


				SetHPageRestoreReserve(page);
		} else if (rc < 0) {


			if (!(vma->vm_flags & VM_MAYSHARE))


				SetHPageRestoreReserve(page);
		} else


			 vma_end_reservation(h, vma, address);
	}
}
