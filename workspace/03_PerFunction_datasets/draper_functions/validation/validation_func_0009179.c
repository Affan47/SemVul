write_b(char *p, char *ebuf, const char *text, size_t len)
{
	if(ebuf - p > len) {
		knh_memcpy(p, text, len);
		return p+len;
	}
	else {
		return NULL;
	}
}
