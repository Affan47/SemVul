freerdp_chanman_process_sync(rdpChanMan* chan_man, freerdp* instance)
{
	void* ldata;
	uint32 ldata_len;
	void* luser_data;
	int lindex;
	struct chan_data* lchan_data;
	struct rdp_chan* lrdp_chan;

	if (chan_man->sync_data == NULL)
		return;

	ldata = chan_man->sync_data;
	ldata_len = chan_man->sync_data_length;
	luser_data = chan_man->sync_user_data;
	lindex = chan_man->sync_index;
	chan_man->sync_data = NULL;
	chan_man->sync_data_length = 0;
	chan_man->sync_user_data = NULL;
	chan_man->sync_index = 0;
	freerdp_sem_signal(chan_man->sync_data_sem);
	lchan_data = chan_man->chans + lindex;
	lrdp_chan = freerdp_chanman_find_rdp_chan_by_name(chan_man, instance->settings,
		lchan_data->name, &lindex);
	if (lrdp_chan != 0)
	{
		IFCALL(instance->SendChannelData, instance, lrdp_chan->chan_id, ldata, ldata_len);
	}
	if (lchan_data->open_event_proc != 0)
	{
		lchan_data->open_event_proc(lchan_data->open_handle,
			CHANNEL_EVENT_WRITE_COMPLETE,
			luser_data, sizeof(void *), sizeof(void *), 0);
	}
}
