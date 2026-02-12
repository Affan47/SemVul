action_remove_thumb (ExifData *ed, ExifLog *log, ExifParams p)
{
	(void) log;
	(void) p;
	if (ed->data) {
		free (ed->data);
		ed->data = NULL;
	}
	ed->size = 0;
}
