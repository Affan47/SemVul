gnttab_init(void)
{
	int i;
	unsigned long max_nr_grant_frames;
	unsigned int max_nr_glist_frames, nr_glist_frames;
	unsigned int nr_init_grefs;
	int ret;

	gnttab_request_version();
	max_nr_grant_frames = gnttab_max_grant_frames();
	nr_grant_frames = 1;


	BUG_ON(grefs_per_grant_frame == 0);
	max_nr_glist_frames = (max_nr_grant_frames *
			       grefs_per_grant_frame / RPP);

	gnttab_list = kmalloc(max_nr_glist_frames * sizeof(grant_ref_t *),
			      GFP_KERNEL);
	if (gnttab_list == NULL)
		return -ENOMEM;

	nr_glist_frames = (nr_grant_frames * grefs_per_grant_frame + RPP - 1) / RPP;
	for (i = 0; i < nr_glist_frames; i++) {
		gnttab_list[i] = (grant_ref_t *)__get_free_page(GFP_KERNEL);
		if (gnttab_list[i] == NULL) {
			ret = -ENOMEM;
			goto ini_nomem;
		}
	}

	ret = arch_gnttab_init(max_nr_grant_frames);
	if (ret < 0)
		goto ini_nomem;

	if (gnttab_setup() < 0) {
		ret = -ENODEV;
		goto ini_nomem;
	}

	nr_init_grefs = nr_grant_frames * grefs_per_grant_frame;

	for (i = NR_RESERVED_ENTRIES; i < nr_init_grefs - 1; i++)
		gnttab_entry(i) = i + 1;

	gnttab_entry(nr_init_grefs - 1) = GNTTAB_LIST_END;
	gnttab_free_count = nr_init_grefs - NR_RESERVED_ENTRIES;
	gnttab_free_head  = NR_RESERVED_ENTRIES;

	printk("Grant table initialized\n");
	return 0;

 ini_nomem:
	for (i--; i >= 0; i--)
		free_page((unsigned long)gnttab_list[i]);
	kfree(gnttab_list);
	return ret;
}
