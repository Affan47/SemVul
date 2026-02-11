on_menu_comment_line1_activate(GtkMenuItem *menuitem, gpointer user_data)
{
	GeanyDocument *doc = document_get_current();
	g_return_if_fail(doc != NULL);

	editor_do_comment(doc->editor, -1, FALSE, FALSE, TRUE);
}
