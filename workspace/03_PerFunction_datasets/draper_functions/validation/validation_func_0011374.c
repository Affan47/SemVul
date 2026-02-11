alloc_node(struct fuse *f)
{
	struct node_slab *slab;
	struct list_head *node;

	if (list_empty(&f->partial_slabs)) {
		int res = alloc_slab(f);
		if (res != 0)
			return NULL;
	}
	slab = list_to_slab(f->partial_slabs.next);
	slab->used++;
	node = slab->freelist.next;
	list_del(node);
	if (list_empty(&slab->freelist)) {
		list_del(&slab->list);
		list_add_tail(&slab->list, &f->full_slabs);
	}
	memset(node, 0, sizeof(struct node));

	return (struct node *) node;
}
