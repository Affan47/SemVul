vmbus_free_channels(void)
{
	struct vmbus_channel *channel, *tmp;

	list_for_each_entry_safe(channel, tmp, &vmbus_connection.chn_list,
		listentry) {

		channel->rescind = true;

		vmbus_device_unregister(channel->device_obj);
	}
}
