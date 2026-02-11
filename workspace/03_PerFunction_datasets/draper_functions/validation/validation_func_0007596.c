brasero_transcode_finalize (GObject *object)
{
	BraseroTranscodePrivate *priv;

	priv = BRASERO_TRANSCODE_PRIVATE (object);

	if (priv->pad_id) {
		g_source_remove (priv->pad_id);
		priv->pad_id = 0;
	}

	brasero_transcode_stop_pipeline (BRASERO_TRANSCODE (object));

	G_OBJECT_CLASS (parent_class)->finalize (object);
}
