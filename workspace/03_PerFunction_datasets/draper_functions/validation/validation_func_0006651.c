parse_xml (GDataParsable *parsable, xmlDoc *doc, xmlNode *node, gpointer user_data, GError **error)
{
	gboolean success;
	GDataPicasaWebUser *self = GDATA_PICASAWEB_USER (parsable);

	if (gdata_parser_is_namespace (node, "http://schemas.google.com/photos/2007") == FALSE)
		return GDATA_PARSABLE_CLASS (gdata_picasaweb_user_parent_class)->parse_xml (parsable, doc, node, user_data, error);

	if (gdata_parser_string_from_element (node, "user", P_REQUIRED | P_NON_EMPTY, &(self->priv->user), &success, error) == TRUE ||
	    gdata_parser_string_from_element (node, "nickname", P_REQUIRED | P_NON_EMPTY, &(self->priv->nickname), &success, error) == TRUE ||
	    gdata_parser_string_from_element (node, "thumbnail", P_REQUIRED | P_NON_EMPTY, &(self->priv->thumbnail_uri), &success, error) == TRUE ||
	    gdata_parser_int64_from_element (node, "quotacurrent", P_REQUIRED | P_NO_DUPES, &(self->priv->quota_current), -1, &success, error) == TRUE ||
	    gdata_parser_int64_from_element (node, "quotalimit", P_REQUIRED | P_NO_DUPES, &(self->priv->quota_limit), -1, &success, error) == TRUE) {
		return success;
	} else if (xmlStrcmp (node->name, (xmlChar*) "maxPhotosPerAlbum") == 0) {

		xmlChar *max_photos_per_album = xmlNodeListGetString (doc, node->children, TRUE);
		self->priv->max_photos_per_album = strtol ((char*) max_photos_per_album, NULL, 10);
		xmlFree (max_photos_per_album);
	} else if (xmlStrcmp (node->name, (xmlChar*) "x-allowDownloads") == 0) {


	} else if (xmlStrcmp (node->name, (xmlChar*) "x-allowPrints") == 0) {


	} else {
		return GDATA_PARSABLE_CLASS (gdata_picasaweb_user_parent_class)->parse_xml (parsable, doc, node, user_data, error);
	}

	return TRUE;
}
