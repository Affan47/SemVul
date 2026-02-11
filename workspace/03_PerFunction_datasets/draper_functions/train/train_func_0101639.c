qpol_role_get_dominate_iter(const qpol_policy_t * policy, const qpol_role_t * datum, qpol_iterator_t ** dominates)
{
	role_datum_t *internal_datum = NULL;
	policydb_t *db = NULL;
	int error;
	ebitmap_state_t *es = NULL;

	if (policy == NULL || datum == NULL || dominates == NULL) {
		if (dominates != NULL)
			*dominates = NULL;
		ERR(policy, "%s", strerror(EINVAL));
		errno = EINVAL;
		return STATUS_ERR;
	}

	internal_datum = (role_datum_t *) datum;
	db = &policy->p->p;

	if (!(es = calloc(1, sizeof(ebitmap_state_t)))) {
		error = errno;
		ERR(policy, "%s", "unable to create iterator state object");
		errno = error;
		return STATUS_ERR;
	}
	es->bmap = &internal_datum->dominates;

	if (qpol_iterator_create(policy, (void *)es, ebitmap_state_get_cur_role,
				 ebitmap_state_next, ebitmap_state_end, ebitmap_state_size, free, dominates)) {
		error = errno;
		free(es);
		errno = error;
		return STATUS_ERR;
	}

	if (es->bmap->node && !ebitmap_get_bit(es->bmap, es->cur))
		ebitmap_state_next(*dominates);

	return STATUS_SUCCESS;
}
