release_pages(struct page **pages, int nr, bool cold)
{
	int i;
	LIST_HEAD(pages_to_free);
	struct zone *zone = NULL;
	struct lruvec *lruvec;
	unsigned long uninitialized_var(flags);
	unsigned int uninitialized_var(lock_batch);

	for (i = 0; i < nr; i++) {
		struct page *page = pages[i];

		if (unlikely(PageCompound(page))) {
			if (zone) {
				spin_unlock_irqrestore(&zone->lru_lock, flags);
				zone = NULL;
			}
			put_compound_page(page);
			continue;
		}


		if (zone && ++lock_batch == SWAP_CLUSTER_MAX) {
			spin_unlock_irqrestore(&zone->lru_lock, flags);
			zone = NULL;
		}

		if (!put_page_testzero(page))
			continue;

		if (PageLRU(page)) {
			struct zone *pagezone = page_zone(page);

			if (pagezone != zone) {
				if (zone)
					spin_unlock_irqrestore(&zone->lru_lock,
									flags);
				lock_batch = 0;
				zone = pagezone;
				spin_lock_irqsave(&zone->lru_lock, flags);
			}

			lruvec = mem_cgroup_page_lruvec(page, zone);
			VM_BUG_ON_PAGE(!PageLRU(page), page);
			__ClearPageLRU(page);
			del_page_from_lru_list(page, lruvec, page_off_lru(page));
		}


		__ClearPageActive(page);

		list_add(&page->lru, &pages_to_free);
	}
	if (zone)
		spin_unlock_irqrestore(&zone->lru_lock, flags);

	mem_cgroup_uncharge_list(&pages_to_free);
	free_hot_cold_page_list(&pages_to_free, cold);
}
