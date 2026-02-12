exif_data_save_data (ExifData *data, unsigned char **d, unsigned int *ds)
{
	if (ds)
		*ds = 0;

	if (!data || !d || !ds)
		return;


	*ds = 14;
	*d = exif_data_alloc (data, *ds);
	if (!*d)  {
		*ds = 0;
		return;
	}
	memcpy (*d, ExifHeader, 6);


	if (data->priv->order == EXIF_BYTE_ORDER_INTEL) {
		memcpy (*d + 6, "II", 2);
	} else {
		memcpy (*d + 6, "MM", 2);
	}


	exif_set_short (*d + 8, data->priv->order, 0x002a);


	exif_set_long (*d + 10, data->priv->order, 8);


	exif_log (data->priv->log, EXIF_LOG_CODE_DEBUG, "ExifData",
		  "Saving IFDs...");
	exif_data_save_data_content (data, data->ifd[EXIF_IFD_0], d, ds,
				     *ds - 6);
	exif_log (data->priv->log, EXIF_LOG_CODE_DEBUG, "ExifData",
		  "Saved %i byte(s) EXIF data.", *ds);
}
