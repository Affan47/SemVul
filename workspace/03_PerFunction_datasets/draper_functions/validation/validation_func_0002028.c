bc_handle_mediainfo_reader_status(xmmsv_t *val, void *userdata)
{
	GMedialib *gml = (GMedialib *)userdata;
	gint32     status;

	xmmsv_get_int(val, &status);
	if (status == 0)
		gml_set_statusbar_text(gml, "Done.");
	else if (status == 1)
		gml_set_statusbar_text(gml, "Reading media info of newly added files...");
	return TRUE;
}
