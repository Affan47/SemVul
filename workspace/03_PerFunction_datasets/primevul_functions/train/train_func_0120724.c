void php_filter_special_chars(PHP_INPUT_FILTER_PARAM_DECL)
{
	unsigned char enc[256] = {0};

	php_filter_strip(value, flags);


	enc['\''] = enc['"'] = enc['<'] = enc['>'] = enc['&'] = enc[0] = 1;


	memset(enc, 1, 32);

	if (flags & FILTER_FLAG_ENCODE_HIGH) {
		memset(enc + 127, 1, sizeof(enc) - 127);
	}

	php_filter_encode_html(value, enc);
}
