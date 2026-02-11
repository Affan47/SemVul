tracker_priority_queue_unref (TrackerPriorityQueue *queue)
{
	if (g_atomic_int_dec_and_test (&queue->ref_count)) {
		g_queue_clear (&queue->queue);
		g_array_free (queue->segments, TRUE);
		g_slice_free (TrackerPriorityQueue, queue);
	}
}
