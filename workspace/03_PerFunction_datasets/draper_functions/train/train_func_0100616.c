free_slab(struct kmem_cache *s, struct page *page)
{
	if (unlikely(s->flags & SLAB_DESTROY_BY_RCU)) {
		struct rcu_head *head;

		if (need_reserve_slab_rcu) {
			int order = compound_order(page);
			int offset = (PAGE_SIZE << order) - s->reserved;

			VM_BUG_ON(s->reserved != sizeof(*head));
			head = page_address(page) + offset;
		} else {
			head = &page->rcu_head;
		}

		call_rcu(head, rcu_free_slab);
	} else
		__free_slab(s, page);
}
