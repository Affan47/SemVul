static int ttm_page_pool_get_pages(struct ttm_page_pool *pool,
				   struct list_head *pages,
				   int ttm_flags,
				   enum ttm_caching_state cstate,
				   unsigned count, unsigned order)
{
	unsigned long irq_flags;
	struct list_head *p;
	unsigned i;
	int r = 0;

	spin_lock_irqsave(&pool->lock, irq_flags);
	if (!order)
		ttm_page_pool_fill_locked(pool, ttm_flags, cstate, count,
					  &irq_flags);

	if (count >= pool->npages) {

		list_splice_init(&pool->list, pages);
		count -= pool->npages;
		pool->npages = 0;
		goto out;
	}


	if (count <= pool->npages/2) {
		i = 0;
		list_for_each(p, &pool->list) {
			if (++i == count)
				break;
		}
	} else {
		i = pool->npages + 1;
		list_for_each_prev(p, &pool->list) {
			if (--i == count)
				break;
		}
	}

	list_cut_position(pages, &pool->list, p);
	pool->npages -= count;
	count = 0;
out:
	spin_unlock_irqrestore(&pool->lock, irq_flags);


	if (ttm_flags & TTM_PAGE_FLAG_ZERO_ALLOC) {
		struct page *page;

		list_for_each_entry(page, pages, lru) {
			if (PageHighMem(page))
				clear_highpage(page);
			else
				clear_page(page_address(page));
		}
	}


	if (count) {
		gfp_t gfp_flags = pool->gfp_flags;


		if (ttm_flags & TTM_PAGE_FLAG_ZERO_ALLOC)
			gfp_flags |= __GFP_ZERO;

		if (ttm_flags & TTM_PAGE_FLAG_NO_RETRY)
			gfp_flags |= __GFP_RETRY_MAYFAIL;


		r = ttm_alloc_new_pages(pages, gfp_flags, ttm_flags, cstate,
					count, order);
	}

	return r;
}
