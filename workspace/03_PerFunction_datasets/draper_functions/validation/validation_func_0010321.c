parse_methods(str* _body, unsigned int* _methods)
{
	str next;
	char *p;
	char *p0;
	unsigned int method;

	if (!_body || !_methods) {
		LM_ERR("invalid parameter value\n");
		return -1;
	}

	next.len = _body->len;
	next.s = _body->s;

	trim_leading(&next);

	*_methods = 0;
	if (next.len == 0) {
		goto done;
	}

	method = 0;
	p = next.s;

	while (p<next.s+next.len) {
		if((p0=parse_method(p, next.s+next.len, &method))!=NULL) {
			*_methods |= method;
			p = p0;
		} else {
			LM_ERR("invalid method [%.*s]\n", next.len, next.s);
			return -1;
		}

		while(p<next.s+next.len && (*p==' ' || *p=='\t'
					|| *p=='\r' || *p=='\n'))
			p++;
		if(p>=next.s+next.len || *p == '\0')
			goto done;


		if (*p == ',')
		{
			p++;
			while(p<next.s+next.len && (*p==' ' || *p=='\t'
					|| *p=='\r' || *p=='\n'))
				p++;
			if(p>=next.s+next.len)
				goto done;
		} else {
			LM_ERR("comma expected\n");
			return -1;
		}
	}

done:
	LM_DBG("methods 0x%X\n", *_methods);
	return 0;
}
