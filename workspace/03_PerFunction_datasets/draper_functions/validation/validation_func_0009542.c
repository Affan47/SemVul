nemo_file_changes_queue_file_moved (GFile *from,
					GFile *to)
{
	NemoFileChange *new_item;
	NemoFileChangesQueue *queue;

	queue = nemo_file_changes_queue_get ();

	new_item = g_new (NemoFileChange, 1);
	new_item->kind = CHANGE_FILE_MOVED;
	new_item->from = g_object_ref (from);
	new_item->to = g_object_ref (to);
	nemo_file_changes_queue_add_common (queue, new_item);
}
