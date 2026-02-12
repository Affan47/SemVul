static time_t round_down_ttl(time_t end_time, int ttl)
{
	if (ttl < 15)
		return end_time;


	if (ttl < 300) {
		end_time = end_time / 10;
		end_time = end_time * 10;
	} else {
		end_time = end_time / 30;
		end_time = end_time * 30;
	}
	return end_time;
}
