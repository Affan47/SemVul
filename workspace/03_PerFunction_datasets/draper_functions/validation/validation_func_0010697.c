gnm_app_clipboard_is_empty (void)
{
	g_return_val_if_fail (app != NULL, TRUE);

	return app->clipboard_sheet_view == NULL;
}
