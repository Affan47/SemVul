ect_edit_select_all (ECellTextView *text_view)
{
	g_return_if_fail (text_view->edit);

	text_view->edit->selection_start = 0;
	text_view->edit->selection_end = strlen (text_view->edit->text);
}
