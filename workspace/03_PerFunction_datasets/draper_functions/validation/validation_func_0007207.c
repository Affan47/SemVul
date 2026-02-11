timestr_to_secs(char *str)
{
	char	expires[256], type;
	time_t	expire_time;

	strcpy(expires,str);
	type = expires[strlen(expires) - 1];

	if(!strchr("dmsh",type))
		return 0L;

	expires[strlen(expires) - 1] = 0;
	expire_time = (time_t)atol(expires);
	if(expire_time == 0L)
		return 0L;

	if(type == 'd')
		expire_time *= 86400;
	else if(type == 'h')
		expire_time *= 3600;
	else if(type == 'm')
		expire_time *= 60;

	return expire_time;
}
