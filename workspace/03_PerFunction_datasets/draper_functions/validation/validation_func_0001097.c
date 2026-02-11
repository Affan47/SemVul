cf_section_find_name2(const CONF_SECTION *section,
				    const char *name1, const char *name2)
{
	const char	*their2;
	CONF_ITEM	*ci;

	if (!section || !name1) return NULL;

	for (ci = cf_sectiontoitem(section); ci; ci = ci->next) {
		if (ci->type != CONF_ITEM_SECTION)
			continue;

		if (strcmp(cf_itemtosection(ci)->name1, name1) != 0)
			continue;

		their2 = cf_itemtosection(ci)->name2;

		if ((!name2 && !their2) ||
		    (name2 && their2 && (strcmp(name2, their2) == 0))) {
			return cf_itemtosection(ci);
		}
	}

	return NULL;
}
