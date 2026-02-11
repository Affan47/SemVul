__iscsi_segment_init(struct iscsi_segment *segment, size_t size,
		     iscsi_segment_done_fn_t *done, struct hash_desc *hash)
{
	memset(segment, 0, sizeof(*segment));
	segment->total_size = size;
	segment->done = done;

	if (hash) {
		segment->hash = hash;
		crypto_hash_init(hash);
	}
}
