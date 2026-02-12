static long add_reservation_in_range(struct resv_map *resv, long f, long t,
				     struct hugetlb_cgroup *h_cg,
				     struct hstate *h, long *regions_needed)
{
	long add = 0;
	struct list_head *head = &resv->regions;
	long last_accounted_offset = f;
	struct file_region *rg = NULL, *trg = NULL;

	if (regions_needed)
		*regions_needed = 0;


	list_for_each_entry_safe(rg, trg, head, link) {

		if (rg->from < f) {


			if (rg->to > last_accounted_offset)
				last_accounted_offset = rg->to;
			continue;
		}


		if (rg->from >= t)
			break;


		if (rg->from > last_accounted_offset)
			add += hugetlb_resv_map_add(resv, rg,
						    last_accounted_offset,
						    rg->from, h, h_cg,
						    regions_needed);

		last_accounted_offset = rg->to;
	}


	if (last_accounted_offset < t)
		add += hugetlb_resv_map_add(resv, rg, last_accounted_offset,
					    t, h, h_cg, regions_needed);

	return add;
}
