usnic_uiom_reg_get(struct usnic_uiom_pd *pd,
						unsigned long addr, size_t size,
						int writable, int dmasync)
{
	struct usnic_uiom_reg *uiomr;
	unsigned long va_base, vpn_start, vpn_last;
	unsigned long npages;
	int offset, err;
	LIST_HEAD(sorted_diff_intervals);


	writable = 1;

	va_base = addr & PAGE_MASK;
	offset = addr & ~PAGE_MASK;
	npages = PAGE_ALIGN(size + offset) >> PAGE_SHIFT;
	vpn_start = (addr & PAGE_MASK) >> PAGE_SHIFT;
	vpn_last = vpn_start + npages - 1;

	uiomr = kmalloc(sizeof(*uiomr), GFP_KERNEL);
	if (!uiomr)
		return ERR_PTR(-ENOMEM);

	uiomr->va = va_base;
	uiomr->offset = offset;
	uiomr->length = size;
	uiomr->writable = writable;
	uiomr->pd = pd;

	err = usnic_uiom_get_pages(addr, size, writable, dmasync,
					&uiomr->chunk_list);
	if (err) {
		usnic_err("Failed get_pages vpn [0x%lx,0x%lx] err %d\n",
				vpn_start, vpn_last, err);
		goto out_free_uiomr;
	}

	spin_lock(&pd->lock);
	err = usnic_uiom_get_intervals_diff(vpn_start, vpn_last,
						(writable) ? IOMMU_WRITE : 0,
						IOMMU_WRITE,
						&pd->rb_root,
						&sorted_diff_intervals);
	if (err) {
		usnic_err("Failed disjoint interval vpn [0x%lx,0x%lx] err %d\n",
						vpn_start, vpn_last, err);
		goto out_put_pages;
	}

	err = usnic_uiom_map_sorted_intervals(&sorted_diff_intervals, uiomr);
	if (err) {
		usnic_err("Failed map interval vpn [0x%lx,0x%lx] err %d\n",
						vpn_start, vpn_last, err);
		goto out_put_intervals;

	}

	err = usnic_uiom_insert_interval(&pd->rb_root, vpn_start, vpn_last,
					(writable) ? IOMMU_WRITE : 0);
	if (err) {
		usnic_err("Failed insert interval vpn [0x%lx,0x%lx] err %d\n",
						vpn_start, vpn_last, err);
		goto out_unmap_intervals;
	}

	usnic_uiom_put_interval_set(&sorted_diff_intervals);
	spin_unlock(&pd->lock);

	return uiomr;

out_unmap_intervals:
	usnic_uiom_unmap_sorted_intervals(&sorted_diff_intervals, pd);
out_put_intervals:
	usnic_uiom_put_interval_set(&sorted_diff_intervals);
out_put_pages:
	usnic_uiom_put_pages(&uiomr->chunk_list, 0);
	spin_unlock(&pd->lock);
out_free_uiomr:
	kfree(uiomr);
	return ERR_PTR(err);
}
