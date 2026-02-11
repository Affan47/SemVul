fcgi_hash_destroy(fcgi_hash *h)
{
	fcgi_hash_buckets *b;
	fcgi_data_seg *p;

	b = h->buckets;
	while (b) {
		fcgi_hash_buckets *q = b;
		b = b->next;
		free(q);
	}
	p = h->data;
	while (p) {
		fcgi_data_seg *q = p;
		p = p->next;
		free(q);
	}
}
