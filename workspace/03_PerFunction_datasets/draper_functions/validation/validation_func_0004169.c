git_config_lookup_map_value(
	git_cvar_map *maps, size_t map_n, const char *value, int *out)
{
	size_t i;

	if (!value)
		return GIT_ENOTFOUND;

	for (i = 0; i < map_n; ++i) {
		git_cvar_map *m = maps + i;

		switch (m->cvar_type) {
		case GIT_CVAR_FALSE:
		case GIT_CVAR_TRUE: {
			int bool_val;

			if (git__parse_bool(&bool_val, value) == 0 &&
				bool_val == (int)m->cvar_type) {
				*out = m->map_value;
				return 0;
			}
			break;
		}

		case GIT_CVAR_INT32:
			if (parse_int32(out, value) == 0)
				return 0;
			break;

		case GIT_CVAR_STRING:
			if (strcasecmp(value, m->str_match) == 0) {
				*out = m->map_value;
				return 0;
			}
			break;
		}
	}

	return GIT_ENOTFOUND;
}
