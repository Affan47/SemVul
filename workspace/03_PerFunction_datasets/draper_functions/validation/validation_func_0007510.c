g_node_count_files ( GNode *file, gpointer data) {
	glong *pcount = data;


	if ( file != NULL) {
		if ( !gw_db_file_is_directory ( file->data)) {
			(*pcount)++;
		}
	}

	return FALSE;
}
