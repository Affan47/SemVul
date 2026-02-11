cgroup_reload_cached_rules(void)
{

	int ret = 0;

	cgroup_dbg("Reloading cached rules from %s.\n", CGRULES_CONF_FILE);
	ret = cgroup_parse_rules(true, CGRULE_INVALID, CGRULE_INVALID, NULL);
	if (ret) {
		cgroup_dbg("Error parsing configuration file \"%s\": %d.\n",
			CGRULES_CONF_FILE, ret);
		ret = ECGRULESPARSEFAIL;
		goto finished;
	}

	#ifdef CGROUP_DEBUG
		cgroup_print_rules_config(stdout);
	#endif

finished:
	return ret;
}
