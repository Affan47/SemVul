ldns_radix_prefix_remainder(radix_strlen_t prefix_len,
	uint8_t* longer_str, radix_strlen_t longer_len,
	uint8_t** split_str, radix_strlen_t* split_len)
{
	*split_len = longer_len - prefix_len;
	*split_str = LDNS_XMALLOC(uint8_t, (*split_len));
	if (!*split_str) {
		return 0;
	}
	memmove(*split_str, longer_str+prefix_len, longer_len-prefix_len);
	return 1;
}
