is_safe_filename(const char * name)
{


	static const uint32_t chclass[8] = {
		0x00000000, 0x00000000,
		0x28800000, 0x000FFFFF,
		0xFFFFFFFC, 0xC03FFFFF,
		0xFFFFFFFC, 0x003FFFFF
	};

	u_int widx, bidx, mask;
	if (!*name)
		return FALSE;

	mask = 1u;
	while (0 != (widx = (u_char)*name++)) {
		bidx = (widx & 15) << 1;
		widx = widx >> 4;
		if (widx >= sizeof(chclass))
			return FALSE;
		if (0 == ((chclass[widx] >> bidx) & mask))
			return FALSE;
		mask |= 2u;
	}
	return TRUE;
}
