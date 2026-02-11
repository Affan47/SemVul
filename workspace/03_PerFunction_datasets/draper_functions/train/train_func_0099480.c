state_setinfo(st_tree_t **nptr, const char *var, const char *val)
{
	while (*nptr) {

		st_tree_t	*node = *nptr;

		if (strcasecmp(node->var, var) > 0) {
			nptr = &node->left;
			continue;
		}

		if (strcasecmp(node->var, var) < 0) {
			nptr = &node->right;
			continue;
		}


		if (!strcasecmp(node->raw, val)) {
			return 0;
		}


		if (node->flags & ST_FLAG_IMMUTABLE) {
			return 0;
		}


		if (node->rawsize < (strlen(val) + 1)) {
			node->rawsize = strlen(val) + 1;
			node->raw = xrealloc(node->raw, node->rawsize);
		}


		snprintf(node->raw, node->rawsize, "%s", val);

		val_escape(node);

		return 1;
	}

	*nptr = xcalloc(1, sizeof(**nptr));

	(*nptr)->var = xstrdup(var);
	(*nptr)->raw = xstrdup(val);
	(*nptr)->rawsize = strlen(val) + 1;

	val_escape(*nptr);

	return 1;
}
