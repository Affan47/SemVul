hash_iterator_init_range (struct hash *hash,
		       struct hash_iterator *hi,
		       bool autolock,
		       int start_bucket,
		       int end_bucket)
{
  if (end_bucket > hash->n_buckets)
    end_bucket = hash->n_buckets;

  ASSERT (start_bucket >= 0 && start_bucket <= end_bucket);

  hi->hash = hash;
  hi->elem = NULL;
  hi->bucket = NULL;
  hi->autolock = autolock;
  hi->last = NULL;
  hi->bucket_marked = false;
  hi->bucket_index_start = start_bucket;
  hi->bucket_index_end = end_bucket;
  hi->bucket_index = hi->bucket_index_start - 1;
}
