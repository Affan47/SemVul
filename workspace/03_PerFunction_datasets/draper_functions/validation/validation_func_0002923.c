get_string_from_tlv(const uint8_t *tlv_msg, int length)
{
	char *str;

	str = g_try_malloc0((sizeof(char) * length) + 1);
	if (str == NULL)
		return NULL;

	memcpy((void *)str, (void *)tlv_msg, length*sizeof(char));

	return str;
}
