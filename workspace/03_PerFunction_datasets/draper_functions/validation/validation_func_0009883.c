qline_delete(const char *mask)
{
	qline_t *q = qline_find(mask);
	mowgli_node_t *n;

	if (!q)
	{
		slog(LG_DEBUG, "qline_delete(): called for nonexistant qline: %s", mask);
		return;
	}

	slog(LG_DEBUG, "qline_delete(): %s -> %s", q->mask, q->reason);


	if (q->duration == 0 || q->expires > CURRTIME)
		unqline_sts("*", q->mask);

	n = mowgli_node_find(q, &qlnlist);
	mowgli_node_delete(n, &qlnlist);
	mowgli_node_free(n);

	free(q->mask);
	free(q->reason);
	free(q->setby);

	mowgli_heap_free(qline_heap, q);

	cnt.qline--;
}
