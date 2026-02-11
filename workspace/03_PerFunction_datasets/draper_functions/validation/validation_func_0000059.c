iiter_set_position (IAnjutaIterable* iter, gint position, GError** e)
{
	gboolean within_range = TRUE;
	gint new_byte_position = 0;
	TextEditorCell* cell = TEXT_EDITOR_CELL(iter);

	if (position > 0)
	{
		const gchar *buffer;
		glong length;

		buffer = (const gchar *)scintilla_send_message (SCINTILLA (cell->priv->editor->scintilla), SCI_GETCHARACTERPOINTER, 0, 0);
		length = g_utf8_strlen (buffer, -1);

		if (position < length)
		{
			gchar *pos;

			pos = g_utf8_offset_to_pointer (buffer, position);
			new_byte_position = pos - buffer;
		}
		else
		{
			position = -1;
			within_range = FALSE;
		}
	}

	if (position < 0)
	{

		new_byte_position =
			scintilla_send_message (SCINTILLA (cell->priv->editor->scintilla),
									SCI_GETLENGTH, 0, 0);
	}

	cell->priv->position = new_byte_position;
	DEBUG_PRINT ("Editor byte position set at: %d", cell->priv->position);
	return within_range;
}
