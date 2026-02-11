mvumi_calculate_checksum(struct mvumi_hs_header *p_header,
							unsigned short len)
{
	unsigned char *ptr;
	unsigned char ret = 0, i;

	ptr = (unsigned char *) p_header->frame_content;
	for (i = 0; i < len; i++) {
		ret ^= *ptr;
		ptr++;
	}

	return ret;
}
