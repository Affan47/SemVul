nautilus_list_model_unload_subdirectory (NautilusListModel *model, GtkTreeIter *iter)
{
	GSequenceIter *child_ptr;
	FileEntry *file_entry, *child_file_entry;
	GtkTreeIter child_iter;

	file_entry = g_sequence_get (iter->user_data);
	if (file_entry->file == NULL ||
	    file_entry->subdirectory == NULL) {
		return;
	}

	file_entry->loaded = 0;


	while (g_sequence_get_length (file_entry->files) > 0) {
		child_ptr = g_sequence_get_begin_iter (file_entry->files);
		child_file_entry = g_sequence_get (child_ptr);
		if (child_file_entry->file == NULL) {

			break;
		} else {
			nautilus_list_model_ptr_to_iter (model, child_ptr, &child_iter);
			nautilus_list_model_remove (model, &child_iter);
		}
	}


	g_signal_emit (model,
		       list_model_signals[SUBDIRECTORY_UNLOADED], 0,
		       file_entry->subdirectory);


	g_hash_table_remove (model->details->directory_reverse_map,
			     file_entry->subdirectory);
	nautilus_directory_unref (file_entry->subdirectory);
	file_entry->subdirectory = NULL;

	g_assert (g_hash_table_size (file_entry->reverse_map) == 0);
	g_hash_table_destroy (file_entry->reverse_map);
	file_entry->reverse_map = NULL;
}
