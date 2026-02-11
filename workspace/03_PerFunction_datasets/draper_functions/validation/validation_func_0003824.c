get_iterations(dns_db_t *db, dns_dbversion_t *ver, dns_rdatatype_t privatetype,
	       unsigned int *iterationsp)
{
	dns_dbnode_t *node = NULL;
	dns_rdata_nsec3param_t nsec3param;
	dns_rdataset_t rdataset;
	isc_result_t result;
	unsigned int iterations = 0;

	dns_rdataset_init(&rdataset);

	result = dns_db_getoriginnode(db, &node);
	if (result != ISC_R_SUCCESS)
		return (result);
	result = dns_db_findrdataset(db, node, ver, dns_rdatatype_nsec3param,
				     0, (isc_stdtime_t) 0, &rdataset, NULL);
	if (result == ISC_R_NOTFOUND)
		goto try_private;
	if (result != ISC_R_SUCCESS)
		goto failure;

	for (result = dns_rdataset_first(&rdataset);
	     result == ISC_R_SUCCESS;
	     result = dns_rdataset_next(&rdataset)) {
		dns_rdata_t rdata = DNS_RDATA_INIT;
		dns_rdataset_current(&rdataset, &rdata);
		CHECK(dns_rdata_tostruct(&rdata, &nsec3param, NULL));
		if ((nsec3param.flags & DNS_NSEC3FLAG_REMOVE) != 0)
			continue;
		if (nsec3param.iterations > iterations)
			iterations = nsec3param.iterations;
	}
	if (result != ISC_R_NOMORE)
		goto failure;

	dns_rdataset_disassociate(&rdataset);

 try_private:
	if (privatetype == 0)
		goto success;

	result = dns_db_findrdataset(db, node, ver, privatetype,
				     0, (isc_stdtime_t) 0, &rdataset, NULL);
	if (result == ISC_R_NOTFOUND)
		goto success;
	if (result != ISC_R_SUCCESS)
		goto failure;

	for (result = dns_rdataset_first(&rdataset);
	     result == ISC_R_SUCCESS;
	     result = dns_rdataset_next(&rdataset)) {
		unsigned char buf[DNS_NSEC3PARAM_BUFFERSIZE];
		dns_rdata_t private = DNS_RDATA_INIT;
		dns_rdata_t rdata = DNS_RDATA_INIT;

		dns_rdataset_current(&rdataset, &rdata);
		if (!dns_nsec3param_fromprivate(&private, &rdata,
						buf, sizeof(buf)))
			continue;
		CHECK(dns_rdata_tostruct(&rdata, &nsec3param, NULL));
		if ((nsec3param.flags & DNS_NSEC3FLAG_REMOVE) != 0)
			continue;
		if (nsec3param.iterations > iterations)
			iterations = nsec3param.iterations;
	}
	if (result != ISC_R_NOMORE)
		goto failure;

 success:
	*iterationsp = iterations;
	result = ISC_R_SUCCESS;

 failure:
	if (node != NULL)
		dns_db_detachnode(db, &node);
	if (dns_rdataset_isassociated(&rdataset))
		dns_rdataset_disassociate(&rdataset);
	return (result);
}
