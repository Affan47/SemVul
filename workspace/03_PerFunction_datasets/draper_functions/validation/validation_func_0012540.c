find_pref(struct dhc6_addr *head, struct iaddr *prefix, u_int8_t plen)
{
	struct dhc6_addr *pref;

	for (pref = head ; pref != NULL ; pref = pref->next) {
		if ((pref->address.len == prefix->len) &&
		    (pref->plen == plen) &&
		    (memcmp(pref->address.iabuf, prefix->iabuf,
			    prefix->len) == 0))
			return pref;
	}

	return NULL;
}
