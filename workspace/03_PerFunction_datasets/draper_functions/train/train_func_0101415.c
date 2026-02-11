journal_reclaim(struct cache_set *c)
{
	struct bkey *k = &c->journal.key;
	struct cache *ca;
	uint64_t last_seq;
	unsigned iter, n = 0;
	atomic_t p;

	while (!atomic_read(&fifo_front(&c->journal.pin)))
		fifo_pop(&c->journal.pin, p);

	last_seq = last_seq(&c->journal);


	for_each_cache(ca, c, iter) {
		struct journal_device *ja = &ca->journal;

		while (ja->last_idx != ja->cur_idx &&
		       ja->seq[ja->last_idx] < last_seq)
			ja->last_idx = (ja->last_idx + 1) %
				ca->sb.njournal_buckets;
	}

	for_each_cache(ca, c, iter)
		do_journal_discard(ca);

	if (c->journal.blocks_free)
		goto out;


	for_each_cache(ca, c, iter) {
		struct journal_device *ja = &ca->journal;
		unsigned next = (ja->cur_idx + 1) % ca->sb.njournal_buckets;


		if (next == ja->discard_idx)
			continue;

		ja->cur_idx = next;
		k->ptr[n++] = MAKE_PTR(0,
				  bucket_to_sector(c, ca->sb.d[ja->cur_idx]),
				  ca->sb.nr_this_dev);
	}

	bkey_init(k);
	SET_KEY_PTRS(k, n);

	if (n)
		c->journal.blocks_free = c->sb.bucket_size >> c->block_bits;
out:
	if (!journal_full(&c->journal))
		__closure_wake_up(&c->journal.wait);
}
