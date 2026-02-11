chase_additional(fetchctx_t *fctx) {
	isc_boolean_t rescan;
	dns_section_t section = DNS_SECTION_ADDITIONAL;
	isc_result_t result;

 again:
	rescan = ISC_FALSE;

	for (result = dns_message_firstname(fctx->rmessage, section);
	     result == ISC_R_SUCCESS;
	     result = dns_message_nextname(fctx->rmessage, section)) {
		dns_name_t *name = NULL;
		dns_rdataset_t *rdataset;
		dns_message_currentname(fctx->rmessage, DNS_SECTION_ADDITIONAL,
					&name);
		if ((name->attributes & DNS_NAMEATTR_CHASE) == 0)
			continue;
		name->attributes &= ~DNS_NAMEATTR_CHASE;
		for (rdataset = ISC_LIST_HEAD(name->list);
		     rdataset != NULL;
		     rdataset = ISC_LIST_NEXT(rdataset, link)) {
			if (CHASE(rdataset)) {
				rdataset->attributes &= ~DNS_RDATASETATTR_CHASE;
				(void)dns_rdataset_additionaldata(rdataset,
								  check_related,
								  fctx);
				rescan = ISC_TRUE;
			}
		}
	}
	if (rescan)
		goto again;
}
