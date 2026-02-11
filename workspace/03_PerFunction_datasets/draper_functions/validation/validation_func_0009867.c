prefs_account_open_cb(GtkAction *action, gpointer data)
{
	MainWindow *mainwin = (MainWindow *)data;
	if (!cur_account) {
		new_account_cb(NULL, mainwin);
	} else {
		account_open(cur_account);
	}
}
