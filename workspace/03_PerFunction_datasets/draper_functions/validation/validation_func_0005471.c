build_all_zonelists(pg_data_t *pgdat, struct zone *zone)
{
	set_zonelist_order();

	if (system_state == SYSTEM_BOOTING) {
		build_all_zonelists_init();
	} else {
#ifdef CONFIG_MEMORY_HOTPLUG
		if (zone)
			setup_zone_pageset(zone);
#endif


		stop_machine(__build_all_zonelists, pgdat, NULL);

	}
	vm_total_pages = nr_free_pagecache_pages();


	if (vm_total_pages < (pageblock_nr_pages * MIGRATE_TYPES))
		page_group_by_mobility_disabled = 1;
	else
		page_group_by_mobility_disabled = 0;

	pr_info("Built %i zonelists in %s order, mobility grouping %s.  "
		"Total pages: %ld\n",
			nr_online_nodes,
			zonelist_order_name[current_zonelist_order],
			page_group_by_mobility_disabled ? "off" : "on",
			vm_total_pages);
#ifdef CONFIG_NUMA
	pr_info("Policy zone: %s\n", zone_names[policy_zone]);
#endif
}
