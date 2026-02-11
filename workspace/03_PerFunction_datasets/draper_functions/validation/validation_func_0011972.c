gw_prioqueue_remove_producer(gw_prioqueue_t *queue)
{
    gw_assert(queue != NULL);

    queue_lock(queue);
    gw_assert(queue->producers > 0);
    queue->producers--;
    pthread_cond_broadcast(&queue->nonempty);
    queue_unlock(queue);
}
