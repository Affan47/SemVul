inet_checksum(void *buf, int buflen)
{
	u32_t sum=0;
	u16_t u16_end=0;
	u16_t *u16_buf = (u16_t *)buf;
	int u16_buflen = buflen >> 1;

	if (buflen % 2)
	{
		*((u8_t *)&u16_end) = ((u8_t *)buf)[buflen-1];
		sum += u16_end;
	}

	while (u16_buflen--)
	{
		sum += u16_buf[u16_buflen];
		if (sum >= 0x00010000)
			sum -= 0x0000ffff;
	}

	return ~sum;
}
