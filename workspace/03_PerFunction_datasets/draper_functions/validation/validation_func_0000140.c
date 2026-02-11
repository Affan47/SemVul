group_get(u_int32_t id)
{
	struct group   *new, *clone;

	if (id < 1 || id > (sizeof(groups) / sizeof(groups[0]))) {
		log_print("group_get: group ID (%u) out of range", id);
		return 0;
	}
	clone = &groups[id - 1];

	new = malloc(sizeof *new);
	if (!new) {
		log_error("group_get: malloc (%lu) failed",
		    (unsigned long)sizeof *new);
		return 0;
	}
	switch (clone->type) {
#ifdef USE_EC
	case EC2N:
		new = ec2n_clone(new, clone);
		break;
#endif
	case MODP:
		new = modp_clone(new, clone);
		break;
	default:
		log_print("group_get: unknown group type %d", clone->type);
		free(new);
		return 0;
	}
	LOG_DBG((LOG_MISC, 70, "group_get: returning %p of group %d", new,
		 new->id));
	return new;
}
