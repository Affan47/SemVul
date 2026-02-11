owner_parse_range(const char *s, unsigned int *from,
                              unsigned int *to, const char *opt)
{
	char *end;


	if (!xtables_strtoui(s, &end, from, 0, UINT32_MAX - 1))
		xtables_param_act(XTF_BAD_VALUE, "owner", opt, s);
	*to = *from;
	if (*end == '-' || *end == ':')
		if (!xtables_strtoui(end + 1, &end, to, 0, UINT32_MAX - 1))
			xtables_param_act(XTF_BAD_VALUE, "owner", opt, s);
	if (*end != '\0')
		xtables_param_act(XTF_BAD_VALUE, "owner", opt, s);
}
