action_self_mount_volume_callback (GtkAction *action,
				   gpointer data)
{
	NemoFile *file;
	NemoView *view;
	GMountOperation *mount_op;

	view = NEMO_VIEW (data);

	file = nemo_view_get_directory_as_file (view);
	if (file == NULL) {
		return;
	}

	mount_op = gtk_mount_operation_new (nemo_view_get_containing_window (view));
	g_mount_operation_set_password_save (mount_op, G_PASSWORD_SAVE_FOR_SESSION);
	nemo_file_mount (file, mount_op, NULL, file_mount_callback, NULL);
	g_object_unref (mount_op);
}
