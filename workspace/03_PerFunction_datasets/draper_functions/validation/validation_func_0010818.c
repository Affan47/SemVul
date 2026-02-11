s_next(struct seq_file *m, void *p, loff_t *pos)
{
	struct vmap_area *va = p, *next;

	++*pos;
	next = list_entry(va->list.next, typeof(*va), list);
	if (&next->list != &vmap_area_list)
		return next;

	return NULL;
}
