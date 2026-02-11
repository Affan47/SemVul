dns64_ttl(dns_db_t *db, dns_dbversion_t *version) {
	dns_dbnode_t *node = NULL;
	dns_rdata_soa_t soa;
	dns_rdata_t rdata = DNS_RDATA_INIT;
	dns_rdataset_t rdataset;
	isc_result_t result;
	isc_uint32_t ttl = ISC_UINT32_MAX;

	dns_rdataset_init(&rdataset);

	result = dns_db_getoriginnode(db, &node);
	if (result != ISC_R_SUCCESS)
		goto cleanup;

	result = dns_db_findrdataset(db, node, version, dns_rdatatype_soa,
				     0, 0, &rdataset, NULL);
	if (result != ISC_R_SUCCESS)
		goto cleanup;
	result = dns_rdataset_first(&rdataset);
	if (result != ISC_R_SUCCESS)
		goto cleanup;

	dns_rdataset_current(&rdataset, &rdata);
	result = dns_rdata_tostruct(&rdata, &soa, NULL);
	RUNTIME_CHECK(result == ISC_R_SUCCESS);
	ttl = ISC_MIN(rdataset.ttl, soa.minimum);

cleanup:
	if (dns_rdataset_isassociated(&rdataset))
		dns_rdataset_disassociate(&rdataset);
	if (node != NULL)
		dns_db_detachnode(db, &node);
	return (ttl);
}
