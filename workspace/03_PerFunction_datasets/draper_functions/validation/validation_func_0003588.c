gst_single_queue_flush (GstMultiQueue * mq, GstSingleQueue * sq, gboolean flush,
    gboolean full)
{
  gboolean result;

  GST_DEBUG_OBJECT (mq, "flush %s queue %d", (flush ? "start" : "stop"),
      sq->id);

  if (flush) {
    GST_MULTI_QUEUE_MUTEX_LOCK (mq);
    sq->srcresult = GST_FLOW_FLUSHING;
    gst_data_queue_set_flushing (sq->queue, TRUE);

    sq->flushing = TRUE;


    GST_LOG_OBJECT (mq, "SingleQueue %d : waking up eventually waiting task",
        sq->id);
    g_cond_signal (&sq->turn);
    sq->last_query = FALSE;
    g_cond_signal (&sq->query_handled);
    GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);

    GST_LOG_OBJECT (mq, "SingleQueue %d : pausing task", sq->id);
    result = gst_pad_pause_task (sq->srcpad);
    sq->sink_tainted = sq->src_tainted = TRUE;
  } else {
    GST_MULTI_QUEUE_MUTEX_LOCK (mq);
    gst_single_queue_flush_queue (sq, full);
    gst_segment_init (&sq->sink_segment, GST_FORMAT_TIME);
    gst_segment_init (&sq->src_segment, GST_FORMAT_TIME);

    sq->srcresult = GST_FLOW_OK;
    sq->pushed = FALSE;
    sq->cur_time = 0;
    sq->max_size.visible = mq->max_size.visible;
    sq->is_eos = FALSE;
    sq->nextid = 0;
    sq->oldid = 0;
    sq->last_oldid = G_MAXUINT32;
    sq->next_time = GST_CLOCK_TIME_NONE;
    sq->last_time = GST_CLOCK_TIME_NONE;
    gst_data_queue_set_flushing (sq->queue, FALSE);


    mq->high_time = GST_CLOCK_TIME_NONE;

    sq->flushing = FALSE;
    GST_MULTI_QUEUE_MUTEX_UNLOCK (mq);

    GST_LOG_OBJECT (mq, "SingleQueue %d : starting task", sq->id);
    result =
        gst_pad_start_task (sq->srcpad, (GstTaskFunction) gst_multi_queue_loop,
        sq->srcpad, NULL);
  }
  return result;
}
