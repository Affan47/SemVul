select_to_anchor(gboolean rectangle)
{
	ScintillaObject *sci = scintilla_get_current();

	if (sci)
		create_selection(sci, select_anchor, select_space, rectangle);
}
