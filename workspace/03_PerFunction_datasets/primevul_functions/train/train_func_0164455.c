static inline int shmem_parse_mpol(char *value, int *policy, nodemask_t *policy_nodes)
{
	char *nodelist = strchr(value, ':');
	int err = 1;

	if (nodelist) {

		*nodelist++ = '\0';
		if (nodelist_parse(nodelist, *policy_nodes))
			goto out;
		if (!nodes_subset(*policy_nodes, node_states[N_HIGH_MEMORY]))
			goto out;
	}
	if (!strcmp(value, "default")) {
		*policy = MPOL_DEFAULT;

		if (!nodelist)
			err = 0;
	} else if (!strcmp(value, "prefer")) {
		*policy = MPOL_PREFERRED;

		if (nodelist) {
			char *rest = nodelist;
			while (isdigit(*rest))
				rest++;
			if (!*rest)
				err = 0;
		}
	} else if (!strcmp(value, "bind")) {
		*policy = MPOL_BIND;

		if (nodelist)
			err = 0;
	} else if (!strcmp(value, "interleave")) {
		*policy = MPOL_INTERLEAVE;


		if (!nodelist)
			*policy_nodes = node_states[N_HIGH_MEMORY];
		err = 0;
	}
out:

	if (nodelist)
		*--nodelist = ':';
	return err;
}
