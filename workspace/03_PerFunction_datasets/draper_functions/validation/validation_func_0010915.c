frle_data_to(const u8 *data, ssize_t size, int fd_out)
{
	int ret;
	const u8 *data_end = data + size;
	u8 tmp;
	u8 buff[MAX_BUFFER_LEN];
	const u8 *p;
	u8 *q, *end_q;
	struct progress_bar prg_bar;

	q = buff;
	end_q = buff + sizeof(buff) - 1;

	progress_bar_init(&prg_bar, size);

	while (data < data_end)
	{
		for (p = data, tmp = *p; tmp == *p && p < data_end; p++);

		if (q >= end_q)
		{
			ret = ffile_writeto(fd_out, buff, q - buff, 0);
			if (ret < 0)
			{
				error_msg("write file failed");
				return NULL;
			}

			q = buff;
		}

		*q++ = p - data;
		*q++ = tmp;

		progress_bar_add(&prg_bar, p - data);

		data = p;
	}

	progress_bar_finish(&prg_bar);

	if (q > buff)
	{
		ret = ffile_writeto(fd_out, buff, q - buff, 0);
		if (ret < 0)
		{
			error_msg("write file failed");
			return NULL;
		}
	}

	return (char *) data;
}
