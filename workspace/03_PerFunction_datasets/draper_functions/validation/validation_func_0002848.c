GetBucket(int depth,
                                              const void* const key[]) {
  RAW_CHECK(LockIsHeld(), "should be held (by this thread)");

  uintptr_t hash = 0;
  for (int i = 0; i < depth; i++) {
    hash += reinterpret_cast<uintptr_t>(key[i]);
    hash += hash << 10;
    hash ^= hash >> 6;
  }
  hash += hash << 3;
  hash ^= hash >> 11;


  unsigned int hash_index = (static_cast<unsigned int>(hash)) % kHashTableSize;
  for (HeapProfileBucket* bucket = bucket_table_[hash_index];
       bucket != 0;
       bucket = bucket->next) {
    if ((bucket->hash == hash) && (bucket->depth == depth) &&
        std::equal(key, key + depth, bucket->stack)) {
      return bucket;
    }
  }


  const size_t key_size = sizeof(key[0]) * depth;
  HeapProfileBucket* bucket;
  if (recursive_insert) {
    const void** key_copy = saved_buckets_keys_[saved_buckets_count_];
    std::copy(key, key + depth, key_copy);
    bucket = &saved_buckets_[saved_buckets_count_];
    memset(bucket, 0, sizeof(*bucket));
    ++saved_buckets_count_;
    bucket->stack = key_copy;
    bucket->next  = NULL;
  } else {
    recursive_insert = true;
    const void** key_copy = static_cast<const void**>(
        MyAllocator::Allocate(key_size));
    recursive_insert = false;
    std::copy(key, key + depth, key_copy);
    recursive_insert = true;
    bucket = static_cast<HeapProfileBucket*>(
        MyAllocator::Allocate(sizeof(HeapProfileBucket)));
    recursive_insert = false;
    memset(bucket, 0, sizeof(*bucket));
    bucket->stack = key_copy;
    bucket->next  = bucket_table_[hash_index];
  }
  bucket->hash = hash;
  bucket->depth = depth;
  bucket_table_[hash_index] = bucket;
  ++num_buckets_;
  return bucket;
}
