interval_insert_memo_cb(GtkWidget * w, gpointer data)
{
	Wiggy *wig = (Wiggy *) data;
	GttTask *newtask;
	if (!wig->interval) return;


	newtask = gtt_interval_get_parent (wig->interval);
	newtask = gtt_task_copy (newtask);
	gtt_task_set_memo (newtask, _("New Diary Entry"));
	gtt_task_set_notes (newtask, "");

	gtt_interval_split (wig->interval, newtask);
	prop_task_dialog_show (newtask);
}
