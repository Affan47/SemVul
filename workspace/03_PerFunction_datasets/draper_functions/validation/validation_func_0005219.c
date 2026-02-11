printf_name_to_id(const char* name, size_t length, unsigned *flags)
{
	char buf[20];
	size_t i;
	print_hash_info *info = hash_info_table;
	unsigned bit;

	if(length > (sizeof(buf)-1)) return 0;
	for(i = 0; i < length; i++) buf[i] = tolower(name[i]);


	if(length == 7 && memcmp(buf, "urlname", 7) == 0) {
		*flags = PRINT_URLNAME;
		return 0;
	} else if(length == 5 && memcmp(buf, "mtime", 5) == 0) {
		*flags = PRINT_MTIME;
		return 0;
	}

	for(bit = 1; bit <= RHASH_ALL_HASHES; bit = bit << 1, info++) {
		if(memcmp(buf, info->short_name, length) == 0 &&
			info->short_name[length] == 0) return bit;
	}
	return 0;
}
