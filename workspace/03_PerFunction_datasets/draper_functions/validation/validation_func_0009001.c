open_in_browser_cb(GtkWidget *widget, FancyViewer *viewer)
{
	debug_print("open outer: %s\n", viewer->cur_link);
	if(viewer->cur_link)
		open_uri(viewer->cur_link, prefs_common_get_uri_cmd());
}
