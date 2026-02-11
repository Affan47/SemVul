buffers_strip_trailing(struct download *d, size_t amount)
{
	struct dl_buffers *b;
	slist_iter_t *iter;
	fileinfo_t *fi;
	size_t n;

	download_check(d);
	g_assert(d->buffers != NULL);

	b = d->buffers;
	fi = d->file_info;

	g_assert(b->mode == DL_BUF_READING);
	g_assert(amount <= b->held);

	if (b->held <= amount) {
		buffers_discard(d);
		return;
	}
	n = b->held - amount;

	iter = slist_iter_removable_on_head(b->list);
	while (slist_iter_has_item(iter)) {
		pmsg_t *mb;
		size_t size;

		mb = slist_iter_current(iter);
		g_assert(mb);

		if (n > 0) {
			size = pmsg_size(mb);
			if (size < n) {
				n -= size;
			} else {
				if (size > n) {
					pmsg_discard_trailing(mb, size - n);
				}
				n = 0;
			}
			slist_iter_next(iter);
		} else {
			pmsg_free(mb);
			slist_iter_remove(iter);
		}
	}
	slist_iter_free(&iter);

	b->held -= amount;

	if (fi->buffered >= amount)
		fi->buffered -= amount;
	else
		fi->buffered = 0;
}
