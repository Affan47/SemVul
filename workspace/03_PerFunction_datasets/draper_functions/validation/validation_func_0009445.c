window_go_to_cb (NemoWindow *window,
		 GError *error,
		 gpointer user_data)
{
	if (error != NULL) {
		g_simple_async_result_set_from_error (display_location_res, error);
	}

	g_simple_async_result_complete (display_location_res);

	g_object_unref (display_location_res);
	display_location_res = NULL;
}
