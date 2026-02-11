find_acl_kw(const char *kw)
{
	int index;
	const char *kwend;
	struct acl_kw_list *kwl;

	kwend = strchr(kw, '(');
	if (!kwend)
		kwend = kw + strlen(kw);

	list_for_each_entry(kwl, &acl_keywords.list, list) {
		for (index = 0; kwl->kw[index].kw != NULL; index++) {
			if ((strncmp(kwl->kw[index].kw, kw, kwend - kw) == 0) &&
			    kwl->kw[index].kw[kwend-kw] == 0)
				return &kwl->kw[index];
		}
	}
	return NULL;
}
