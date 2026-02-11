db_journal_writer_append_resource (JournalWriter *jwriter,
                                   gint           s_id,
                                   const gchar   *uri)
{
	gint o_len;
	DataFormat df;
	gint size;

	g_return_val_if_fail (jwriter->journal > 0, FALSE);

	o_len = strlen (uri);
	df = DATA_FORMAT_RESOURCE_INSERT;
	size = (sizeof (guint32) * 2) + o_len + 1;

	cur_block_maybe_expand (jwriter, size);

	cur_setnum (jwriter->cur_block, &(jwriter->cur_pos), df);
	cur_setnum (jwriter->cur_block, &(jwriter->cur_pos), s_id);
	cur_setstr (jwriter->cur_block, &(jwriter->cur_pos), uri, o_len);

	jwriter->cur_entry_amount++;
	jwriter->cur_block_len += size;

	return TRUE;
}
