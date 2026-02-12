static int move_to_new_page(struct page *newpage, struct page *page)
{
	struct address_space *mapping;
	int rc;


	if (TestSetPageLocked(newpage))
		BUG();


	newpage->index = page->index;
	newpage->mapping = page->mapping;

	mapping = page_mapping(page);
	if (!mapping)
		rc = migrate_page(mapping, newpage, page);
	else if (mapping->a_ops->migratepage)


		rc = mapping->a_ops->migratepage(mapping,
						newpage, page);
	else
		rc = fallback_migrate_page(mapping, newpage, page);

	if (!rc) {
		mem_cgroup_page_migration(page, newpage);
		remove_migration_ptes(page, newpage);
	} else
		newpage->mapping = NULL;

	unlock_page(newpage);

	return rc;
}
