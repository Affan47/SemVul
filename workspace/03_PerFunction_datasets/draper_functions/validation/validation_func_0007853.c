gtk_source_completion_words_get_start_iter (GtkSourceCompletionProvider *provider,
                                            GtkSourceCompletionContext  *context,
                                            GtkSourceCompletionProposal *proposal,
                                            GtkTextIter                 *iter)
{
	gchar *word;
	glong nb_chars;

	gtk_source_completion_context_get_iter (context, iter);

	word = get_word_at_iter (iter);
	g_return_val_if_fail (word != NULL, FALSE);

	nb_chars = g_utf8_strlen (word, -1);
	gtk_text_iter_backward_chars (iter, nb_chars);

	g_free (word);
	return TRUE;
}
