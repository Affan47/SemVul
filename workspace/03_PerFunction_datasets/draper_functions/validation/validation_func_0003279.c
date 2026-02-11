icq_snac_ref_find(session_t *s, uint32_t ref) {
	icq_private_t *j;
	icq_snac_reference_list_t *l;

	if (!s || !(j = s->priv) || (!j->snac_ref_list) || (ref > 0xffff))
		return NULL;

	for (l = j->snac_ref_list; l; l = l->next) {
		if (l->ref == ref)
			return l;
	}
	return NULL;
}
