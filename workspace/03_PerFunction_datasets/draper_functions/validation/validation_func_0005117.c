brasero_song_control_get_length (BraseroSongControl *self)
{
	BraseroSongControlPrivate *priv;

	priv = BRASERO_SONG_CONTROL_PRIVATE (self);
	if (!priv->uri)
		return -1;

	return priv->end - priv->start;
}
