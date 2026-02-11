tree_popup_activate_cb(GtkCheckMenuItem *item, gpointer user_data)
{
	GtkWindow *dialog = g_object_get_data(G_OBJECT(item), "dialog");

	switch (GPOINTER_TO_INT(user_data))
	{
		case ACTION_ADD:
		{
			add_button_click_cb(NULL, dialog);
			break;
		}
		case ACTION_EDIT:
		{
			edit_button_click_cb(NULL, dialog);
			break;
		}
		case ACTION_DELETE:
		{
			delete_button_click_cb(NULL, dialog);
			break;
		}
	}
}
