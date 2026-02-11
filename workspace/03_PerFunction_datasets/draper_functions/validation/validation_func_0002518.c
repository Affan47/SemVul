file_list_attributes_identical (GList *file_list, const char *attribute_name)
{
	gboolean identical;
	char *first_attr;
	GList *l;

	first_attr = NULL;
	identical = TRUE;

	for (l = file_list; l != NULL; l = l->next) {
		NemoFile *file;

		file = NEMO_FILE (l->data);

		if (nemo_file_is_gone (file)) {
			continue;
		}

		if (first_attr == NULL) {
			first_attr = nemo_file_get_string_attribute_with_default (file, attribute_name);
		} else {
			char *attr;
			attr = nemo_file_get_string_attribute_with_default (file, attribute_name);
			if (strcmp (attr, first_attr)) {
				identical = FALSE;
				g_free (attr);
				break;
			}
			g_free (attr);
		}
	}

	g_free (first_attr);
	return identical;
}
