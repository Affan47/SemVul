_gcr_record_set_base64 (GcrRecord *record,
                        guint column,
                        gconstpointer data,
                        gsize n_data)
{
	GcrRecordBlock *block;
	gint state, save;
	gsize estimate;
	gsize length;

	g_return_if_fail (record != NULL);
	g_return_if_fail (column < record->n_columns);

	estimate = n_data * 4 / 3 + n_data * 4 / (3 * 65) + 7;
	block = record_block_new (NULL, estimate);


	state = save = 0;
	length = g_base64_encode_step ((guchar *)data, n_data, FALSE,
	                               block->value, &state, &save);
	length += g_base64_encode_close (TRUE, block->value + length,
	                                 &state, &save);
	block->value[length] = 0;
	g_assert (length < estimate);

	g_strchomp (block->value);
	record_take_column (record, column, block);
}
