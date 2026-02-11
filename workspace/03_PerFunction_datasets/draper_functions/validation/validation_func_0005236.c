linux_if_inet6_next(isc_interfaceiter_t *iter) {
	if (iter->proc != NULL &&
	    fgets(iter->entry, sizeof(iter->entry), iter->proc) != NULL)
		iter->valid = ISC_R_SUCCESS;
	else
		iter->valid = ISC_R_NOMORE;
	return (iter->valid);
}
