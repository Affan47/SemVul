prepend_automatic_keywords (NemoFile *file,
			    GList *names)
{

	NemoFile *parent;

	parent = nemo_file_get_parent (file);

#ifdef TRASH_IS_FAST_ENOUGH
	if (nemo_file_is_in_trash (file)) {
		names = g_list_prepend
			(names, g_strdup (NEMO_FILE_EMBLEM_NAME_TRASH));
	}
#endif
	if (file_has_note (file)) {
		names = g_list_prepend
			(names, g_strdup (NEMO_FILE_EMBLEM_NAME_NOTE));
	}


	if (!nemo_file_can_write (file) &&
	    !nemo_file_is_in_trash (file) &&
	    (parent == NULL || nemo_file_can_write (parent))) {
		names = g_list_prepend
			(names, g_strdup (NEMO_FILE_EMBLEM_NAME_CANT_WRITE));
	}
	if (!nemo_file_can_read (file)) {
		names = g_list_prepend
			(names, g_strdup (NEMO_FILE_EMBLEM_NAME_CANT_READ));
	}
	if (nemo_file_is_symbolic_link (file)) {
		names = g_list_prepend
			(names, g_strdup (NEMO_FILE_EMBLEM_NAME_SYMBOLIC_LINK));
	}

	if (parent) {
		nemo_file_unref (parent);
	}


	return names;
}
