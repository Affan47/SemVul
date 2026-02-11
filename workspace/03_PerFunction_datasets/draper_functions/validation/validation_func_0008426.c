clear_cb(GtkButton *button, gpointer user_data)
{
	PlaylistWindow *playlist_window = (PlaylistWindow *) user_data;
	if (playlist_window) {
		stop_cb(NULL, (gpointer) playlist_window->GetPlaylist());
		GDK_THREADS_LEAVE();
		playlist_window->GetPlaylist()->Clear();
		GDK_THREADS_ENTER();
	}
}
