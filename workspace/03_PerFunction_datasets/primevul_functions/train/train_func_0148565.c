static int unix_instantiate(CONF_SECTION *conf, void **instance)
{
	struct unix_instance *inst;


	inst = *instance = rad_malloc(sizeof(*inst));
	if (!inst) {
		return -1;
	}
	memset(inst, 0, sizeof(*inst));


	if (cf_section_parse(conf, inst, module_config) < 0) {
		unix_detach(inst);
		return -1;
	}


	paircompare_register(PW_GROUP, PW_USER_NAME, groupcmp, NULL);
#ifdef PW_GROUP_NAME
	paircompare_register(PW_GROUP_NAME, PW_USER_NAME, groupcmp, NULL);
#endif

#undef inst

	return 0;
}
