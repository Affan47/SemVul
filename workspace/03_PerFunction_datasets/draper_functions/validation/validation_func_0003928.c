work_queue_task_specify_file_piece(struct work_queue_task *t, const char *local_name, const char *remote_name, off_t start_byte, off_t end_byte, int type, int flags)
{
	struct list *files;
	struct work_queue_file *tf;
	if(!t || !local_name || !remote_name) {
		return 0;
	}


	if(remote_name[0] == '/') {
		return 0;
	}

	if(end_byte < start_byte) {
		return 0;
	}

	if(type == WORK_QUEUE_INPUT) {
		files = t->input_files;
	} else {
		files = t->output_files;
	}

	list_first_item(files);
	while((tf = (struct work_queue_file*)list_next_item(files))) {
		if(!strcmp(remote_name, tf->remote_name))
		{	return 0;	}
	}

	tf = work_queue_file_create(remote_name, WORK_QUEUE_FILE_PIECE, flags);

	tf->length = strlen(local_name);
	tf->offset = start_byte;
	tf->piece_length = end_byte - start_byte + 1;
	tf->payload = xxstrdup(local_name);

	list_push_tail(files, tf);
	return 1;
}
