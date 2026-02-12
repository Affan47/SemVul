static int ttm_page_pool_free(struct ttm_page_pool *pool, unsigned nr_free,
			      bool use_static)
{
	static struct page *static_buf[NUM_PAGES_TO_ALLOC];
	unsigned long irq_flags;
	struct page *p;
	struct page **pages_to_free;
	unsigned freed_pages = 0,
		 npages_to_free = nr_free;

	if (NUM_PAGES_TO_ALLOC < nr_free)
		npages_to_free = NUM_PAGES_TO_ALLOC;

	if (use_static)
		pages_to_free = static_buf;
	else
		pages_to_free = kmalloc_array(npages_to_free,
					      sizeof(struct page *),
					      GFP_KERNEL);
	if (!pages_to_free) {
		pr_debug("Failed to allocate memory for pool free operation\n");
		return 0;
	}

restart:
	spin_lock_irqsave(&pool->lock, irq_flags);

	list_for_each_entry_reverse(p, &pool->list, lru) {
		if (freed_pages >= npages_to_free)
			break;

		pages_to_free[freed_pages++] = p;

		if (freed_pages >= NUM_PAGES_TO_ALLOC) {

			__list_del(p->lru.prev, &pool->list);

			ttm_pool_update_free_locked(pool, freed_pages);


			spin_unlock_irqrestore(&pool->lock, irq_flags);

			ttm_pages_put(pages_to_free, freed_pages, pool->order);
			if (likely(nr_free != FREE_ALL_PAGES))
				nr_free -= freed_pages;

			if (NUM_PAGES_TO_ALLOC >= nr_free)
				npages_to_free = nr_free;
			else
				npages_to_free = NUM_PAGES_TO_ALLOC;

			freed_pages = 0;


			if (nr_free)
				goto restart;


			goto out;

		}
	}


	if (freed_pages) {
		__list_del(&p->lru, &pool->list);

		ttm_pool_update_free_locked(pool, freed_pages);
		nr_free -= freed_pages;
	}

	spin_unlock_irqrestore(&pool->lock, irq_flags);

	if (freed_pages)
		ttm_pages_put(pages_to_free, freed_pages, pool->order);
out:
	if (pages_to_free != static_buf)
		kfree(pages_to_free);
	return nr_free;
}
