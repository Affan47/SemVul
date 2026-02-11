rfc822_encode_domain(const char *address,
			    const char *charset)
{
	const struct unicode_info *ui=unicode_find(charset);
	const char *cp;
	char *p, *q;

	if (!ui)
	{
		errno=EINVAL;
		return NULL;
	}

	p=unicode_convert(address, ui, &unicode_UTF8);

	if (!p)
		return NULL;

	cp=strchr(p, '@');

	if (!cp)
	{
		q=rfc822_encode_domain_int("", 0, p);
		free(p);
		return q;
	}

	++cp;
	q=rfc822_encode_domain_int(p, cp-p, cp);
	free(p);
	return q;
}
