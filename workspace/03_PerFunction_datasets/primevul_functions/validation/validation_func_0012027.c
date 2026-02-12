static int migrate_page_add(struct page *page, struct list_head *pagelist,
				unsigned long flags)
{
	struct page *head = compound_head(page);


	if ((flags & MPOL_MF_MOVE_ALL) || page_mapcount(head) == 1) {
		if (!isolate_lru_page(head)) {
			list_add_tail(&head->lru, pagelist);
			mod_node_page_state(page_pgdat(head),
				NR_ISOLATED_ANON + page_is_file_cache(head),
				hpage_nr_pages(head));
		} else if (flags & MPOL_MF_STRICT) {


			return -EIO;
		}
	}

	return 0;
}
