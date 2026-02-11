jdns_copy_array(const unsigned char *src, int size)
{
	unsigned char *out;
	if(size <= 0)
		return 0;
	out = (unsigned char *)jdns_alloc(size);
	memcpy(out, src, size);
	return out;
}
