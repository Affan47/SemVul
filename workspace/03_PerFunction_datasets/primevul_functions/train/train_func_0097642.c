void clear_vma_resv_huge_pages(struct vm_area_struct *vma)
{


	struct resv_map *reservations = vma_resv_map(vma);

	if (reservations && is_vma_resv_set(vma, HPAGE_RESV_OWNER)) {
		resv_map_put_hugetlb_cgroup_uncharge_info(reservations);
		kref_put(&reservations->refs, resv_map_release);
	}

	reset_vma_resv_huge_pages(vma);
}
