strip_escape(struct ipset_session *session, char *str)
{
	if (STRNEQ(str, IPSET_ESCAPE_START, 1)) {
		if (!STREQ(str + strlen(str) - 1, IPSET_ESCAPE_END)) {
			syntax_err("cannot find closing escape character "
				   "'%s' in %s", IPSET_ESCAPE_END, str);
			return NULL;
		}
		str++;
		str[strlen(str) - 1] = '\0';
	}
	return str;
}
