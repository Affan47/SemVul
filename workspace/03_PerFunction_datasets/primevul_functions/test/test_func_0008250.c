void *mempool_getbuffer(MemoryPoolHandle handle, size_t expected_buffer_size) {
  int rc;
  int bufs_to_allocate;
  int bufs_that_can_be_allocated = 0;
  struct memory_pool_element *pool_item = NULL;
  struct mempool *pool = (struct mempool *)handle;
  char *log_msg_fmt =
      "mempool(%p): mempool_getbuffer called for invalid "
      "expected_buffer_size(%zu), current pool manages only "
      "mempool_item_size(%zu)";
  char log_msg[300];

  if (pool == NULL) {
    return NULL;
  }

  if (pool->mempool_item_size != expected_buffer_size) {

    if (pool->log_callback_func) {
      snprintf(log_msg, sizeof(log_msg), log_msg_fmt, (void *)pool,
               expected_buffer_size, pool->mempool_item_size);
      pool->log_callback_func(MEMPOOL_LOG_FATAL, log_msg);
      return NULL;
    }
  }

  if ((pool->flags & ENABLE_LOCKING) != 0) {
    pthread_mutex_lock(&pool->lock);
  }


  if (pool->free_bufs_in_pool == 0) {
    bufs_to_allocate = pool->expandable_size / pool->mempool_item_size;
    bufs_that_can_be_allocated = pool_can_expand_by(pool);
    if (bufs_that_can_be_allocated > 0) {


      bufs_to_allocate = ((bufs_to_allocate > bufs_that_can_be_allocated)
                              ? bufs_that_can_be_allocated
                              : bufs_to_allocate);

      rc = freelist_allocate(pool, bufs_to_allocate);
      if (rc != 0) {
        if ((pool->flags & ENABLE_LOCKING) != 0) {
          pthread_mutex_unlock(&pool->lock);
        }
        return NULL;
      }
    } else {

      if ((pool->flags & ENABLE_LOCKING) != 0) {
        pthread_mutex_unlock(&pool->lock);
      }
      return NULL;
    }
  }


  if (pool->free_list != NULL) {
    pool_item = pool->free_list;
    pool->free_list = pool_item->next;
    pool_item->next = (struct memory_pool_element *)NULL;
    pool->free_bufs_in_pool--;
  }

  if (pool_item) {
    pool->number_of_bufs_shared++;
  }

  if ((pool->flags & ENABLE_LOCKING) != 0) {
    pthread_mutex_unlock(&pool->lock);
  }

  return (void *)pool_item;
}
