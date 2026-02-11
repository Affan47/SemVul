get_word_iter (GtkTextBuffer *buffer,
	       GtkTextIter   *start_word,
	       GtkTextIter   *end_word)
{
	gtk_text_buffer_get_iter_at_mark (buffer,
	                                  end_word,
	                                  gtk_text_buffer_get_insert (buffer));

	*start_word = *end_word;

	while (gtk_text_iter_backward_char (start_word))
	{
		gunichar ch = gtk_text_iter_get_char (start_word);

		if (is_separator (ch))
		{
			gtk_text_iter_forward_char (start_word);
			return;
		}
	}
}
