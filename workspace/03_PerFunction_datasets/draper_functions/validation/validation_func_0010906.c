ck_event_logger_queue_event (CkEventLogger      *event_logger,
                             CkLogEvent         *event,
                             GError            **error)
{
        CkLogEvent *event_copy;
        gboolean    ret;

        g_return_val_if_fail (CK_IS_EVENT_LOGGER (event_logger), FALSE);
        g_return_val_if_fail (event != NULL, FALSE);

        event_copy = ck_log_event_copy (event);

        g_async_queue_push (event_logger->priv->event_queue,
                            event_copy);

        ret = TRUE;

        return ret;
}
