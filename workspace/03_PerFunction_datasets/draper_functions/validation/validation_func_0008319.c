sst_byt_stream_operations(struct sst_byt *byt, int type,
				     int stream_id, int wait)
{
	u64 header;

	header = sst_byt_header(type, 0, false, stream_id);
	if (wait)
		return sst_ipc_tx_message_wait(&byt->ipc, header, NULL,
						0, NULL, 0);
	else
		return sst_ipc_tx_message_nowait(&byt->ipc, header,
						NULL, 0);
}
