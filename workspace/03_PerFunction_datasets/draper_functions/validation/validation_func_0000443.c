copy_gfile_special(MainInfo *min, DirPane *src, DirPane *dst, GFile *from, GFile *to, GError **err)
{
	GFileInfo	*fi;
	gchar		*path;
	gboolean	ok = FALSE;

	if((fi = g_file_query_info(from, "standard::*,unix::*", G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS, NULL, err)) == NULL)
		return FALSE;


	if((path = g_file_get_path(to)) != NULL)
	{
		const guint32	mode = g_file_info_get_attribute_uint32(fi, G_FILE_ATTRIBUTE_UNIX_MODE);
		const guint32	rdev = g_file_info_get_attribute_uint32(fi, G_FILE_ATTRIBUTE_UNIX_RDEV);


		if(mode & S_IFIFO)
			ok = mkfifo(path, mode) == 0;
		else
			ok = mknod(path, mode, rdev) == 0;

		if(!ok)
		{
			const gchar	*fmt = (mode & S_IFIFO) ? _("Error copying FIFO: %s") : _("Error copying special file: %s");
			g_set_error(err, g_io_error_quark(), g_io_error_from_errno(errno), fmt, strerror(errno));
		}
		g_free(path);
	}
	else
		g_set_error(err, g_io_error_quark(), G_IO_ERROR_FAILED, _("Error copying special file: no local path"));

	g_object_unref(fi);

	return ok;
}
