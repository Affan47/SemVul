brasero_player_bacon_setup_pipe (BraseroPlayerBacon *bacon)
{
	GstElement *video_sink, *audio_sink;
	GstBus *bus = NULL;
	gdouble volume;
	gpointer value;

	bacon->priv->pipe = gst_element_factory_make ("playbin", NULL);
	if (!bacon->priv->pipe) {
		g_warning ("Pipe creation error : can't create pipe.\n");
		return;
	}

	audio_sink = gst_element_factory_make ("gsettingsaudiosink", NULL);
	if (audio_sink)
		g_object_set (G_OBJECT (bacon->priv->pipe),
			      "audio-sink", audio_sink,
			      NULL);


#if 0
	else
		goto error;
#endif

	video_sink = gst_element_factory_make ("gsettingsvideosink", NULL);
	if (video_sink) {
		GstElement *element;

		g_object_set (G_OBJECT (bacon->priv->pipe),
			      "video-sink", video_sink,
			      NULL);

		element = gst_bin_get_by_interface (GST_BIN (video_sink),
						    GST_TYPE_VIDEO_OVERLAY);
		if (element && GST_IS_VIDEO_OVERLAY (element))
			bacon->priv->xoverlay = GST_VIDEO_OVERLAY (element);
	}

	bus = gst_pipeline_get_bus (GST_PIPELINE (bacon->priv->pipe));


	gst_bus_set_sync_handler (bus,
				  (GstBusSyncHandler) brasero_player_bacon_bus_messages_handler,
				  bacon, NULL);
	gst_bus_add_watch (bus,
			   (GstBusFunc) brasero_player_bacon_bus_messages,
			   bacon);
	gst_object_unref (bus);


	brasero_setting_get_value (brasero_setting_get_default (),
	                           BRASERO_SETTING_PLAYER_VOLUME,
	                           &value);
	volume = GPOINTER_TO_INT (value);
	volume = CLAMP (volume, 0, 100);
	g_object_set (bacon->priv->pipe,
		      "volume", (gdouble) volume / 100.0,
		      NULL);

	return;

#if 0
error:
	g_message ("player creation error");
	brasero_player_bacon_clear_pipe (bacon);
	g_signal_emit (bacon,
		       brasero_player_bacon_signals [STATE_CHANGED_SIGNAL],
		       0,
		       BACON_STATE_ERROR);
	gtk_widget_queue_resize (GTK_WIDGET (bacon));
#endif
}
