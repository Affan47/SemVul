gtk_source_completion_words_library_get_proposal (GSequenceIter *iter)
{
	if (iter == NULL)
	{
		return NULL;
	}

	return GTK_SOURCE_COMPLETION_WORDS_PROPOSAL (g_sequence_get (iter));
}
