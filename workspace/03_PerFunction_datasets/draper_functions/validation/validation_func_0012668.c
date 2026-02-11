cli_realhex2ui(const char *hex, uint16_t *ptr, unsigned int len) {
	uint16_t val;
	unsigned int i;
	int c;

    for(i = 0; i < len; i += 2) {
	val = 0;

	if(hex[i] == '?' && hex[i + 1] == '?') {
	    val |= CLI_MATCH_IGNORE;

	} else if(hex[i + 1] == '?') {
	    if((c = cli_hex2int(hex[i])) >= 0) {
		val = c << 4;
	    } else {
		return 0;
	    }
	    val |= CLI_MATCH_NIBBLE_HIGH;

	} else if(hex[i] == '?') {
	    if((c = cli_hex2int(hex[i + 1])) >= 0) {
		val = c;
	    } else {
		return 0;
	    }
	    val |= CLI_MATCH_NIBBLE_LOW;

	} else if(hex[i] == '(') {
	    val |= CLI_MATCH_SPECIAL;

	} else {
	    if((c = cli_hex2int(hex[i])) >= 0) {
		val = c;
		if((c = cli_hex2int(hex[i+1])) >= 0) {
		    val = (val << 4) + c;
		} else {
		    return 0;
		}
	    } else {
		return 0;
	    }
	}

	*ptr++ = val;
    }
    return 1;
}
