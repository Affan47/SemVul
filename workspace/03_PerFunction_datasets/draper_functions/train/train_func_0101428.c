string_netstringlen(size_t namlen, size_t vallen, const void* value)
{
	HA_MSG_ASSERT(value);
	HA_MSG_ASSERT( vallen == strlen(value));

	return binary_netstringlen(namlen, vallen, value);
}
