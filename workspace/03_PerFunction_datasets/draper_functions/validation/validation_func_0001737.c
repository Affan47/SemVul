brasero_metadata_create_mp3_pipeline (BraseroMetadata *self)
{
	BraseroMetadataPrivate *priv;
	GstElement *source;
	GstElement *parse;
	GstElement *sink;
	GstBus *bus;

	priv = BRASERO_METADATA_PRIVATE (self);

	priv->pipeline_mp3 = gst_pipeline_new (NULL);

	source = gst_element_make_from_uri (GST_URI_SRC,
					    priv->info->uri,
					    NULL, NULL);
	if (!source) {
		priv->error = g_error_new (BRASERO_UTILS_ERROR,
					   BRASERO_UTILS_ERROR_GENERAL,
					   _("%s element could not be created"),
					   "\"Source\"");

		g_object_unref (priv->pipeline_mp3);
		priv->pipeline_mp3 = NULL;
		return FALSE;
	}
	gst_bin_add (GST_BIN (priv->pipeline_mp3), source);

	parse = gst_element_factory_make ("mpegaudioparse", NULL);
	if (!parse) {
		priv->error = g_error_new (BRASERO_UTILS_ERROR,
					   BRASERO_UTILS_ERROR_GENERAL,
					   _("%s element could not be created"),
					   "\"mpegaudioparse\"");

		g_object_unref (priv->pipeline_mp3);
		priv->pipeline_mp3 = NULL;
		return FALSE;
	}
	gst_bin_add (GST_BIN (priv->pipeline_mp3), parse);

	sink = gst_element_factory_make ("fakesink", NULL);
	if (!sink) {
		priv->error = g_error_new (BRASERO_UTILS_ERROR,
					   BRASERO_UTILS_ERROR_GENERAL,
					   _("%s element could not be created"),
					   "\"Fakesink\"");

		g_object_unref (priv->pipeline_mp3);
		priv->pipeline_mp3 = NULL;
		return FALSE;
	}
	gst_bin_add (GST_BIN (priv->pipeline_mp3), sink);


	if (!gst_element_link_many (source, parse, sink, NULL)) {
		g_object_unref (priv->pipeline_mp3);
		priv->pipeline_mp3 = NULL;
		return FALSE;
	}


	bus = gst_pipeline_get_bus (GST_PIPELINE (priv->pipeline_mp3));
	priv->watch_mp3 = gst_bus_add_watch (bus,
					     (GstBusFunc) brasero_metadata_mp3_bus_messages,
					     self);
	gst_object_unref (bus);

	gst_element_set_state (priv->pipeline_mp3, GST_STATE_PLAYING);
	return TRUE;
}
