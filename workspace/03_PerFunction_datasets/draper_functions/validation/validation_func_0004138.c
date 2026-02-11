brasero_track_stream_set_source (BraseroTrackStream *track,
				 const gchar *uri)
{
	BraseroTrackStreamClass *klass;
	BraseroBurnResult res;

	g_return_val_if_fail (BRASERO_IS_TRACK_STREAM (track), BRASERO_BURN_ERR);

	klass = BRASERO_TRACK_STREAM_GET_CLASS (track);
	if (!klass->set_source)
		return BRASERO_BURN_ERR;

	res = klass->set_source (track, uri);
	if (res != BRASERO_BURN_OK)
		return res;

	brasero_track_changed (BRASERO_TRACK (track));
	return BRASERO_BURN_OK;
}
