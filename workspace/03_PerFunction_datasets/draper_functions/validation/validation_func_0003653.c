eog_image_save_by_info (EogImage *img, EogImageSaveInfo *source, GError **error)
{
	EogImagePrivate *priv;
	EogImageStatus prev_status;
	gboolean success = FALSE;
	GFile *tmp_file;
	char *tmp_file_path;

	g_return_val_if_fail (EOG_IS_IMAGE (img), FALSE);
	g_return_val_if_fail (EOG_IS_IMAGE_SAVE_INFO (source), FALSE);

	priv = img->priv;

	prev_status = priv->status;


	priv->status = EOG_IMAGE_STATUS_SAVING;


	if (source->exists && !source->modified) {
		return TRUE;
	}


	if (priv->image == NULL) {
		g_set_error (error, EOG_IMAGE_ERROR,
			     EOG_IMAGE_ERROR_NOT_LOADED,
			     _("No image loaded."));
		return FALSE;
	}


	if (!check_if_file_is_writable (priv->file)) {
		g_set_error (error, EOG_IMAGE_ERROR,
			     EOG_IMAGE_ERROR_NOT_SAVED,
			     _("You do not have the permissions necessary to save the file."));
		return FALSE;
	}


	tmp_file = tmp_file_get ();

	if (tmp_file == NULL) {
		g_set_error (error, EOG_IMAGE_ERROR,
			     EOG_IMAGE_ERROR_TMP_FILE_FAILED,
			     _("Temporary file creation failed."));
		return FALSE;
	}

	tmp_file_path = g_file_get_path (tmp_file);

#ifdef HAVE_JPEG

	if ((g_ascii_strcasecmp (source->format, EOG_FILE_FORMAT_JPEG) == 0) &&
	    source->exists && source->modified)
	{
		success = eog_image_jpeg_save_file (img, tmp_file_path, source, NULL, error);
	}
#endif

	if (!success && (*error == NULL)) {
		success = gdk_pixbuf_save (priv->image, tmp_file_path, source->format, error, NULL);
	}

	if (success) {

		success = tmp_file_move_to_uri (img, tmp_file, priv->file, TRUE , error);
	}

	if (success) {
		eog_image_reset_modifications (img);
	}

	tmp_file_delete (tmp_file);

	g_free (tmp_file_path);
	g_object_unref (tmp_file);

	priv->status = prev_status;

	return success;
}
