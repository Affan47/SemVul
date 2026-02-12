static void free_hpage_workfn(struct work_struct *work)
{
	struct llist_node *node;

	node = llist_del_all(&hpage_freelist);

	while (node) {
		struct page *page;
		struct hstate *h;

		page = container_of((struct address_space **)node,
				     struct page, mapping);
		node = node->next;
		page->mapping = NULL;


		h = size_to_hstate(page_size(page));

		__update_and_free_page(h, page);

		cond_resched();
	}
}
