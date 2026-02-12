client_pattern_compare(char *ip, char *name)
{
	int i = 0;


	for (i = 0; i < pattc; i++) {
		if (patterns[i].type == TRUSTCLIENT) {


			if (regexec(&patterns[i].regexv, ip, 0, 0, 0) == 0) {
				if (debug != 0)
					ci_debug_printf(2, "DEBUG client_pattern_compare: trustclient (%s) matched: %s\n", patterns[i].pattern, ip);
				return 1;


			} else if ((name != NULL) && (regexec(&patterns[i].regexv, name, 0, 0, 0) == 0)) {
				if (debug != 0)
					ci_debug_printf(2, "DEBUG client_pattern_compare: trustclient (%s) matched: %s\n", patterns[i].pattern, name);
				return 2;
			}
		}
	}


	return 0;
}
