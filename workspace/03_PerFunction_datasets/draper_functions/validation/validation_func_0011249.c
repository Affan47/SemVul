extract_mp4(f_state *s, u_int64_t c_offset, unsigned char *foundat, u_int64_t buflen,
						   s_spec *needle, u_int64_t f_offset)
{
	unsigned char	*buf = foundat;

	unsigned char	*extractbuf = NULL;
	unsigned int	size = 0;
	u_int64_t		file_size = 0;


	while(1)
	{
	 	size=htoi(&foundat[28],FOREMOST_BIG_ENDIAN);
		if(size ==0)
		{

			foundat+=28;
			break;
		}

		if(size > 0 && size < buflen)
		{
			if(!isprint(foundat[32]) ||  !isprint(foundat[33]))
			{

				break;

			}
			foundat+=size;

		}
		else
		{
			if (size < needle->max_len)
			{

				return NULL;
			}
			else
			{


				break;
			}
		}


	}
	if (foundat)
	{
		file_size = (foundat - buf) + needle->footer_len;
		if (file_size < 1 * KILOBYTE)
			return buf + needle->header_len;
	}


	if (file_size > buflen)
		file_size = buflen;
	foundat = buf;


	extractbuf = buf;
	write_to_disk(s, needle, file_size, extractbuf, c_offset + f_offset);
	foundat += file_size;
	return foundat;
}
