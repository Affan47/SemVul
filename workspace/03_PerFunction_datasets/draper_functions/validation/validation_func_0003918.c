slapi_apib_register(char *guid, void **api )
{
	int ret = -1;
	ABAPI *item;

	if(buffer_lock == 0)
	{
		if(0 == (buffer_lock = slapi_new_mutex()))

			return -1;
	}


	item = (ABAPI*)slapi_ch_malloc(sizeof(ABAPI));
	if(item)
	{
		item->guid = guid;
		item->api = api;

		slapi_lock_mutex(buffer_lock);
		if(head == NULL)
		{
			head = item;
			head->next = head;
			head->prev = head;
		}
		else
		{
			item->next = head;
			item->prev = head->prev;
			head->prev = item;
			item->prev->next = item;
		}
		slapi_unlock_mutex(buffer_lock);

		ret = 0;
	}

	return ret;
}
