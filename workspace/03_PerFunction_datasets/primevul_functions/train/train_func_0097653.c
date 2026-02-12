bool hugetlb_reserve_pages(struct inode *inode,
					long from, long to,
					struct vm_area_struct *vma,
					vm_flags_t vm_flags)
{
	long chg, add = -1;
	struct hstate *h = hstate_inode(inode);
	struct hugepage_subpool *spool = subpool_inode(inode);
	struct resv_map *resv_map;
	struct hugetlb_cgroup *h_cg = NULL;
	long gbl_reserve, regions_needed = 0;


	if (from > to) {
		VM_WARN(1, "%s called with a negative range\n", __func__);
		return false;
	}


	if (vm_flags & VM_NORESERVE)
		return true;


	if (!vma || vma->vm_flags & VM_MAYSHARE) {


		resv_map = inode_resv_map(inode);

		chg = region_chg(resv_map, from, to, &regions_needed);

	} else {

		resv_map = resv_map_alloc();
		if (!resv_map)
			return false;

		chg = to - from;

		set_vma_resv_map(vma, resv_map);
		set_vma_resv_flags(vma, HPAGE_RESV_OWNER);
	}

	if (chg < 0)
		goto out_err;

	if (hugetlb_cgroup_charge_cgroup_rsvd(hstate_index(h),
				chg * pages_per_huge_page(h), &h_cg) < 0)
		goto out_err;

	if (vma && !(vma->vm_flags & VM_MAYSHARE) && h_cg) {


		resv_map_set_hugetlb_cgroup_uncharge_info(resv_map, h_cg, h);
	}


	gbl_reserve = hugepage_subpool_get_pages(spool, chg);
	if (gbl_reserve < 0)
		goto out_uncharge_cgroup;


	if (hugetlb_acct_memory(h, gbl_reserve) < 0)
		goto out_put_pages;


	if (!vma || vma->vm_flags & VM_MAYSHARE) {
		add = region_add(resv_map, from, to, regions_needed, h, h_cg);

		if (unlikely(add < 0)) {
			hugetlb_acct_memory(h, -gbl_reserve);
			goto out_put_pages;
		} else if (unlikely(chg > add)) {


			long rsv_adjust;


			hugetlb_cgroup_uncharge_cgroup_rsvd(
				hstate_index(h),
				(chg - add) * pages_per_huge_page(h), h_cg);

			rsv_adjust = hugepage_subpool_put_pages(spool,
								chg - add);
			hugetlb_acct_memory(h, -rsv_adjust);
		} else if (h_cg) {


			hugetlb_cgroup_put_rsvd_cgroup(h_cg);
		}
	}
	return true;

out_put_pages:

	(void)hugepage_subpool_put_pages(spool, chg);
out_uncharge_cgroup:
	hugetlb_cgroup_uncharge_cgroup_rsvd(hstate_index(h),
					    chg * pages_per_huge_page(h), h_cg);
out_err:
	if (!vma || vma->vm_flags & VM_MAYSHARE)


		if (chg >= 0 && add < 0)
			region_abort(resv_map, from, to, regions_needed);
	if (vma && is_vma_resv_set(vma, HPAGE_RESV_OWNER))
		kref_put(&resv_map->refs, resv_map_release);
	return false;
}
