encode_disk_name(char *ptr, unsigned int n)
{
	if (n >= 26)
		ptr = encode_disk_name(ptr, n / 26 - 1);
	*ptr = 'a' + n % 26;
	return ptr + 1;
}
