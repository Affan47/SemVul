handle_message_tag_time (const char *time, message_tags_data *tags_data)
{


	if (!*time)
		return;

	if (time[strlen (time) - 1] == 'Z')
	{

		struct tm t;
		int z;


		z = sscanf (time, "%d-%d-%dT%d:%d:%d", &t.tm_year, &t.tm_mon, &t.tm_mday,
					&t.tm_hour, &t.tm_min, &t.tm_sec);

		if (z != 6)
			return;

		t.tm_year -= 1900;
		t.tm_mon -= 1;
		t.tm_isdst = 0;

		tags_data->timestamp = mktime (&t);

		if (tags_data->timestamp < 0)
		{
			tags_data->timestamp = 0;
			return;
		}


		tags_data->timestamp -= get_timezone();
	}
	else
	{

		long long int t;


		if (sscanf (time, "%lld", &t) != 1)
			return;

		tags_data->timestamp = (time_t) t;
	}
}
