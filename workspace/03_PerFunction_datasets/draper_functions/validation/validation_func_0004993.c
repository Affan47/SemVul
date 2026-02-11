my_gettext(unsigned char *s)
{
	if (gettext_ht) {
		unsigned char *r = htfind(gettext_ht, s);
		if (r)
			s = r;
	}
	if (s[0] == '|')
		return ignore_prefix(s);
	else
		return s;
}
