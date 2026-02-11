brasero_burn_unlock_src_media (BraseroBurn *burn,
			       GError **error)
{
	BraseroBurnPrivate *priv = BRASERO_BURN_PRIVATE (burn);
	BraseroMedium *medium;

	if (!priv->src)
		return BRASERO_BURN_OK;


	medium = brasero_drive_get_medium (priv->src);
	if (priv->mounted_by_us) {
		brasero_burn_unmount (burn, medium, error);
		priv->mounted_by_us = FALSE;
	}

	if (brasero_drive_is_locked (priv->src, NULL))
		brasero_drive_unlock (priv->src);


	priv->src = NULL;
	return BRASERO_BURN_OK;
}
