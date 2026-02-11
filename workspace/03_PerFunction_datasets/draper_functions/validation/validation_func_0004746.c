mem_crc16(u16 crc, const char *buff, size_t size)
{
	const char *buff_end = buff + size;

	while (buff < buff_end)
	{
		crc = crc16_table[((crc >> 8) ^ (*buff++)) & 0xFF] ^ (crc << 8);
	}

	return crc;
}
