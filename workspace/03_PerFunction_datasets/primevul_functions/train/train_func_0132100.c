int check_submodule_name(const char *name)
{

	if (!*name)
		return -1;


	goto in_component;
	while (*name) {
		char c = *name++;
		if (c == '/' || c == '\\') {
in_component:
			if (name[0] == '.' && name[1] == '.' &&
			    (!name[2] || name[2] == '/' || name[2] == '\\'))
				return -1;
		}
	}

	return 0;
}
