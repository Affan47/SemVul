brasero_drive_is_fake (BraseroDrive *drive)
{
	BraseroDrivePrivate *priv;

	g_return_val_if_fail (drive != NULL, FALSE);
	g_return_val_if_fail (BRASERO_IS_DRIVE (drive), FALSE);

	priv = BRASERO_DRIVE_PRIVATE (drive);
	return (priv->device == NULL);
}
