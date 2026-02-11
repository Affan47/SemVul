gst_data_queue_push (GstDataQueue * queue, GstDataQueueItem * item)
{
  g_return_val_if_fail (GST_IS_DATA_QUEUE (queue), FALSE);
  g_return_val_if_fail (item != NULL, FALSE);

  GST_DATA_QUEUE_MUTEX_LOCK_CHECK (queue, flushing);

  STATUS (queue, "before pushing");


  if (gst_data_queue_locked_is_full (queue)) {
    GST_DATA_QUEUE_MUTEX_UNLOCK (queue);
    if (G_LIKELY (queue->fullcallback))
      queue->fullcallback (queue, queue->checkdata);
    else
      g_signal_emit (queue, gst_data_queue_signals[SIGNAL_FULL], 0);
    GST_DATA_QUEUE_MUTEX_LOCK_CHECK (queue, flushing);


    while (gst_data_queue_locked_is_full (queue)) {
      queue->abidata.ABI.waiting_del = TRUE;
      g_cond_wait (queue->item_del, queue->qlock);
      queue->abidata.ABI.waiting_del = FALSE;
      if (queue->flushing)
        goto flushing;
    }
  }

  g_queue_push_tail (queue->queue, item);

  if (item->visible)
    queue->cur_level.visible++;
  queue->cur_level.bytes += item->size;
  queue->cur_level.time += item->duration;

  STATUS (queue, "after pushing");
  if (queue->abidata.ABI.waiting_add)
    g_cond_signal (queue->item_add);

  GST_DATA_QUEUE_MUTEX_UNLOCK (queue);

  return TRUE;


flushing:
  {
    GST_DEBUG ("queue:%p, we are flushing", queue);
    GST_DATA_QUEUE_MUTEX_UNLOCK (queue);
    return FALSE;
  }
}
