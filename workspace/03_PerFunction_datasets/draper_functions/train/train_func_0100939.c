get_file_to_call(time_t filetime, char type)
{
	static file_list **ptr = NULL;
	static int         cnt;
	static time_t      _filetime;
	int interval;

	if (filetime == 0)
	{
		if (ptr != NULL)
		{
			ptr++;
			cnt--;
		}
	}
	else
	{
		ptr = file_root;
		cnt = file_root_member;
		_filetime = filetime;
	}

	while (cnt > 0 && (interval = time_in_interval((*ptr)->time,_filetime,type)) < 1)
	{
		if (interval == 0 && (*ptr)->used == 0 && (*ptr)->type == type)
		{
			(*ptr)->used = 1;
			return (*ptr);
		}

		ptr++;
		cnt--;
	}

	return NULL;
}
