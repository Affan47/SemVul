crc32_block_endian1(uint32_t val, const void *buf, unsigned len, uint32_t *crc_table)
{
	const void *end = (uint8_t*)buf + len;

	while (buf != end) {
		val = (val << 8) ^ crc_table[(val >> 24) ^ *(uint8_t*)buf];
		buf = (uint8_t*)buf + 1;
	}
	return val;
}
