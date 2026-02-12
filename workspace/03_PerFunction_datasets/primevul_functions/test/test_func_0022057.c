static int unmap_and_move(new_page_t get_new_page, unsigned long private,
			struct page *page, int force)
{
	int rc = 0;
	int *result = NULL;
	struct page *newpage = get_new_page(page, private, &result);
	int rcu_locked = 0;
	int charge = 0;

	if (!newpage)
		return -ENOMEM;

	if (page_count(page) == 1)

		goto move_newpage;

	rc = -EAGAIN;
	if (TestSetPageLocked(page)) {
		if (!force)
			goto move_newpage;
		lock_page(page);
	}

	if (PageWriteback(page)) {
		if (!force)
			goto unlock;
		wait_on_page_writeback(page);
	}


	if (PageAnon(page)) {
		rcu_read_lock();
		rcu_locked = 1;
	}


	if (!page->mapping) {
		if (!PageAnon(page) && PagePrivate(page)) {


			try_to_free_buffers(page);
		}
		goto rcu_unlock;
	}

	charge = mem_cgroup_prepare_migration(page);

	try_to_unmap(page, 1);

	if (!page_mapped(page))
		rc = move_to_new_page(newpage, page);

	if (rc) {
		remove_migration_ptes(page, page);
		if (charge)
			mem_cgroup_end_migration(page);
	} else if (charge)
 		mem_cgroup_end_migration(newpage);
rcu_unlock:
	if (rcu_locked)
		rcu_read_unlock();

unlock:

	unlock_page(page);

	if (rc != -EAGAIN) {


 		list_del(&page->lru);
 		move_to_lru(page);
	}

move_newpage:


	move_to_lru(newpage);
	if (result) {
		if (rc)
			*result = rc;
		else
			*result = page_to_nid(newpage);
	}
	return rc;
}
