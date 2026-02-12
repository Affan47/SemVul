uint_to_str_back_len(char *ptr, guint32 value, int len)
{
	char *new_ptr;

	new_ptr = uint_to_str_back(ptr, value);


	len -= (int)(ptr - new_ptr);


	while (len > 0)
	{
		*(--new_ptr) = '0';
		len--;
	}

	return new_ptr;
}
