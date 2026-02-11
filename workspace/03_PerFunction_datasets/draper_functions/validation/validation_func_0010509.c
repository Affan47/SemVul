_save_data_track_xml (xmlTextWriter *project,
		      BraseroBurnSession *session)
{
	gchar *uri;
	gint success;
	GSList *iter;
	GSList *tracks;
	GSList *grafts;
	gchar *filename;
	BraseroTrackDataCfg *track;

	tracks = brasero_burn_session_get_tracks (session);
	track = BRASERO_TRACK_DATA_CFG (tracks->data);

	filename = brasero_track_data_cfg_get_icon_path (track);
	if (filename) {

		success = xmlTextWriterWriteElement (project, (xmlChar *) "icon", (xmlChar *) filename);
		g_free (filename);
		if (success < 0)
			return FALSE;
	}

	grafts = brasero_track_data_get_grafts (BRASERO_TRACK_DATA (track));
	for (; grafts; grafts = grafts->next) {
		BraseroGraftPt *graft;

		graft = grafts->data;

		success = xmlTextWriterStartElement (project, (xmlChar *) "graft");
		if (success < 0)
			return FALSE;

		success = xmlTextWriterWriteElement (project, (xmlChar *) "path", (xmlChar *) graft->path);
		if (success < 0)
			return FALSE;

		if (graft->uri) {
			xmlChar *escaped;

			escaped = (unsigned char *) g_uri_escape_string (graft->uri, NULL, FALSE);
			success = xmlTextWriterWriteElement (project, (xmlChar *) "uri", escaped);
			g_free (escaped);
			if (success < 0)
				return FALSE;
		}

		success = xmlTextWriterEndElement (project);
		if (success < 0)
			return FALSE;
	}


	iter = brasero_track_data_get_excluded_list (BRASERO_TRACK_DATA (track));
	for (; iter; iter = iter->next) {
		xmlChar *escaped;

		escaped = xmlURIEscapeStr ((xmlChar *) iter->data, NULL);
		success = xmlTextWriterWriteElement (project, (xmlChar *) "excluded", (xmlChar *) escaped);
		g_free (escaped);
		if (success < 0)
			return FALSE;
	}


	iter = brasero_track_data_cfg_get_restored_list (track);
	for (; iter; iter = iter->next) {
		uri = iter->data;
		success = xmlTextWriterWriteElement (project, (xmlChar *) "restored", (xmlChar *) uri);
		if (success < 0)
			return FALSE;
	}


	return TRUE;
}
