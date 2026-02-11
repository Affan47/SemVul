save_state_data(const void *data, uint32 len)
{
	uint32		padlen = MAXALIGN(len);

	if (padlen > records.bytes_free)
	{
		records.tail->next = palloc0(sizeof(StateFileChunk));
		records.tail = records.tail->next;
		records.tail->len = 0;
		records.tail->next = NULL;
		records.num_chunks++;

		records.bytes_free = Max(padlen, 512);
		records.tail->data = palloc(records.bytes_free);
	}

	memcpy(((char *) records.tail->data) + records.tail->len, data, len);
	records.tail->len += padlen;
	records.bytes_free -= padlen;
	records.total_len += padlen;
}
