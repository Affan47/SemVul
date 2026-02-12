int build_detached_freelist(struct kmem_cache *s, size_t size,
			    void **p, struct detached_freelist *df)
{
	size_t first_skipped_index = 0;
	int lookahead = 3;
	void *object;
	struct page *page;


	df->page = NULL;

	do {
		object = p[--size];

	} while (!object && size);

	if (!object)
		return 0;

	page = virt_to_head_page(object);
	if (!s) {

		if (unlikely(!PageSlab(page))) {
			BUG_ON(!PageCompound(page));
			kfree_hook(object);
			__free_pages(page, compound_order(page));
			p[size] = NULL;
			return size;
		}

		df->s = page->slab_cache;
	} else {
		df->s = cache_from_obj(s, object);
	}


	df->page = page;
	set_freepointer(df->s, object, NULL);
	df->tail = object;
	df->freelist = object;
	p[size] = NULL;
	df->cnt = 1;

	while (size) {
		object = p[--size];
		if (!object)
			continue;


		if (df->page == virt_to_head_page(object)) {

			set_freepointer(df->s, object, df->freelist);
			df->freelist = object;
			df->cnt++;
			p[size] = NULL;

			continue;
		}


		if (!--lookahead)
			break;

		if (!first_skipped_index)
			first_skipped_index = size + 1;
	}

	return first_skipped_index;
}
