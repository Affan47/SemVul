get_smiley_by_name_and_service(const char *name, const char *service)
{
	smiley *psmile, *possibility = NULL;
	LList *l;
	for (l = smileys; l; l = l_list_next(l)) {
		psmile = (smiley *)(l->data);
		if (strcasecmp(psmile->name, name) != 0)
			continue;
		if (!service || (psmile->service
				&& !strcasecmp(psmile->service, service)))
			return psmile;
		if (!possibility)
			possibility = psmile;
	}
	return possibility;
}
