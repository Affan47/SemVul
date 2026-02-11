zbud_alloc(struct zbud_pool *pool, size_t size, gfp_t gfp,
			unsigned long *handle)
{
	int chunks, i, freechunks;
	struct zbud_header *zhdr = NULL;
	enum buddy bud;
	struct page *page;

	if (!size || (gfp & __GFP_HIGHMEM))
		return -EINVAL;
	if (size > PAGE_SIZE - ZHDR_SIZE_ALIGNED - CHUNK_SIZE)
		return -ENOSPC;
	chunks = size_to_chunks(size);
	spin_lock(&pool->lock);


	zhdr = NULL;
	for_each_unbuddied_list(i, chunks) {
		if (!list_empty(&pool->unbuddied[i])) {
			zhdr = list_first_entry(&pool->unbuddied[i],
					struct zbud_header, buddy);
			list_del(&zhdr->buddy);
			if (zhdr->first_chunks == 0)
				bud = FIRST;
			else
				bud = LAST;
			goto found;
		}
	}


	spin_unlock(&pool->lock);
	page = alloc_page(gfp);
	if (!page)
		return -ENOMEM;
	spin_lock(&pool->lock);
	pool->pages_nr++;
	zhdr = init_zbud_page(page);
	bud = FIRST;

found:
	if (bud == FIRST)
		zhdr->first_chunks = chunks;
	else
		zhdr->last_chunks = chunks;

	if (zhdr->first_chunks == 0 || zhdr->last_chunks == 0) {

		freechunks = num_free_chunks(zhdr);
		list_add(&zhdr->buddy, &pool->unbuddied[freechunks]);
	} else {

		list_add(&zhdr->buddy, &pool->buddied);
	}


	if (!list_empty(&zhdr->lru))
		list_del(&zhdr->lru);
	list_add(&zhdr->lru, &pool->lru);

	*handle = encode_handle(zhdr, bud);
	spin_unlock(&pool->lock);

	return 0;
}
