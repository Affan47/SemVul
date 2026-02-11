print_success(const char *val)
{
        int res;

	if (isdigit(*val)) {
	        errno = 0;
        	res = strtoul(val, NULL, 10);
	        if (errno) {
			char *out;
			if (asprintf(&out, "conversion error(%s)", val) < 0)
				out = NULL;
	                return out;
        	}

	        return strdup(aulookup_success(res));
	} else
		return strdup(val);
}
