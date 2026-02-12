action_create_value (ExifData *ed, ExifLog *log, ExifTag tag, ExifIfd ifd)
{
	ExifEntry *e;

	if (!((e = exif_content_get_entry (ed->ifd[ifd], tag)))) {
	    exif_log (log, EXIF_LOG_CODE_DEBUG, "exif", _("Adding entry..."));
	    e = exif_entry_new ();
	    exif_content_add_entry (ed->ifd[ifd], e);
	    exif_entry_initialize (e, tag);

	    exif_entry_unref(e);
	}
	return e;
}
