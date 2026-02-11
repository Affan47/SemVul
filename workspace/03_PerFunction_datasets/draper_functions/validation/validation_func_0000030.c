cli_md5buff(const unsigned char *buffer, unsigned int len, unsigned char *dig)
{
	unsigned char digest[16];
	char *md5str, *pt;
	int i;

    cl_hash_data("md5", buffer, len, digest, NULL);

    if(dig)
	memcpy(dig, digest, 16);

    if(!(md5str = (char *) cli_calloc(32 + 1, sizeof(char))))
	return NULL;

    pt = md5str;
    for(i = 0; i < 16; i++) {
	sprintf(pt, "%02x", digest[i]);
	pt += 2;
    }

    return md5str;
}
