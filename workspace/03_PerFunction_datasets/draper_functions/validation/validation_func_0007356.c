ario_audioscrobbler_submit_queue_cb (SoupSession *session, SoupMessage *msg, gpointer user_data)
#else
static void
ario_audioscrobbler_submit_queue_cb (SoupMessage *msg, gpointer user_data)
#endif
{
        ARIO_LOG_FUNCTION_START
        ArioAudioscrobbler *audioscrobbler = ARIO_AUDIOSCROBBLER (user_data);

        ARIO_LOG_DBG ("Submission response");
        ario_audioscrobbler_parse_response (audioscrobbler, msg);

        if (audioscrobbler->priv->status == STATUS_OK) {
                ARIO_LOG_DBG ("Queue submitted successfully");
                ario_audioscrobbler_free_queue_entries (audioscrobbler, &audioscrobbler->priv->submission);
                audioscrobbler->priv->submission = g_queue_new ();
                ario_audioscrobbler_save_queue (audioscrobbler);

                audioscrobbler->priv->submit_count += audioscrobbler->priv->queue_count;
                audioscrobbler->priv->queue_count = 0;

                g_free (audioscrobbler->priv->submit_time);
                audioscrobbler->priv->submit_time = ario_utf_friendly_time (time (NULL));
        } else {
                ++audioscrobbler->priv->failures;


                ario_g_queue_concat (audioscrobbler->priv->submission,
                                     audioscrobbler->priv->queue);
                g_assert (g_queue_is_empty (audioscrobbler->priv->queue));
                g_queue_free (audioscrobbler->priv->queue);
                audioscrobbler->priv->queue = audioscrobbler->priv->submission;
                audioscrobbler->priv->submission = g_queue_new ();;
                ario_audioscrobbler_save_queue (audioscrobbler);

                ario_audioscrobbler_print_queue (audioscrobbler, FALSE);

                if (audioscrobbler->priv->failures >= 3) {
                        ARIO_LOG_INFO ("Queue submission has failed %d times; caching tracks locally",
                                       audioscrobbler->priv->failures);
                        g_free (audioscrobbler->priv->status_msg);

                        audioscrobbler->priv->handshake = FALSE;
                        audioscrobbler->priv->status = GIVEN_UP;
                        audioscrobbler->priv->status_msg = NULL;
                } else {
                        ARIO_LOG_INFO ("Queue submission failed %d times", audioscrobbler->priv->failures);
                }
        }

        ario_audioscrobbler_preferences_sync (audioscrobbler);
        g_idle_add ((GSourceFunc) idle_unref_cb, audioscrobbler);
}
