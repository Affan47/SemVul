cli_hex2str_to(const char *hex, char *ptr, size_t len)
{
    size_t i;
    int c;
    char val;

    for(i = 0; i < len; i += 2) {
	if((c = cli_hex2int(hex[i])) >= 0) {
	    val = c;
	    if((c = cli_hex2int(hex[i+1])) >= 0) {
		val = (val << 4) + c;
	    } else {
		return -1;
	    }
	} else {
	    return -1;
	}

	*ptr++ = val;
    }

    return 0;
}
