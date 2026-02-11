adc_msg_unescape_to_target(const char* string, char* target, size_t target_size)
{
	size_t w = 0;
	char* ptr = (char*) target;
	char* str = (char*) string;
	int escaped = 0;

	while (*str && w < (target_size-1))
	{
		if (escaped) {
			if (*str == 's')
				*ptr++ = ' ';
			else if (*str == '\\')
				*ptr++ = '\\';
			else if (*str == 'n')
				*ptr++ = '\n';
			else
				*ptr++ = *str;
			w++;
			escaped = 0;
		} else {
			if (*str == '\\')
				escaped = 1;
			else
			{
				*ptr++ = *str;
				w++;
			}
		}
		str++;
	}
	*ptr = 0;
	w++;
	return w;
}
