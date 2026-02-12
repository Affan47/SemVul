getquestions(isc_buffer_t *source, dns_message_t *msg, dns_decompress_t *dctx,
	     unsigned int options)
{
	isc_region_t r;
	unsigned int count;
	dns_name_t *name;
	dns_name_t *name2;
	dns_offsets_t *offsets;
	dns_rdataset_t *rdataset;
	dns_rdatalist_t *rdatalist;
	isc_result_t result;
	dns_rdatatype_t rdtype;
	dns_rdataclass_t rdclass;
	dns_namelist_t *section;
	bool free_name;
	bool best_effort;
	bool seen_problem;

	section = &msg->sections[DNS_SECTION_QUESTION];

	best_effort = ((options & DNS_MESSAGEPARSE_BESTEFFORT) != 0);
	seen_problem = false;

	name = NULL;
	rdataset = NULL;
	rdatalist = NULL;

	for (count = 0; count < msg->counts[DNS_SECTION_QUESTION]; count++) {
		name = isc_mempool_get(msg->namepool);
		if (name == NULL)
			return (ISC_R_NOMEMORY);
		free_name = true;

		offsets = newoffsets(msg);
		if (offsets == NULL) {
			result = ISC_R_NOMEMORY;
			goto cleanup;
		}
		dns_name_init(name, *offsets);


		isc_buffer_remainingregion(source, &r);
		isc_buffer_setactive(source, r.length);
		result = getname(name, source, msg, dctx);
		if (result != ISC_R_SUCCESS)
			goto cleanup;


		result = findname(&name2, name, section);


		if (result != ISC_R_SUCCESS) {
			if (!ISC_LIST_EMPTY(*section))
				DO_ERROR(DNS_R_FORMERR);
			ISC_LIST_APPEND(*section, name, link);
			free_name = false;
		} else {
			isc_mempool_put(msg->namepool, name);
			name = name2;
			name2 = NULL;
			free_name = false;
		}


		isc_buffer_remainingregion(source, &r);
		if (r.length < 4) {
			result = ISC_R_UNEXPECTEDEND;
			goto cleanup;
		}
		rdtype = isc_buffer_getuint16(source);
		rdclass = isc_buffer_getuint16(source);


		if (msg->rdclass_set == 0) {
			msg->rdclass = rdclass;
			msg->rdclass_set = 1;
		} else if (msg->rdclass != rdclass)
			DO_ERROR(DNS_R_FORMERR);


		if (rdtype == dns_rdatatype_tkey)
			msg->tkey = 1;


		result = dns_message_find(name, rdclass, rdtype, 0, NULL);
		if (result == ISC_R_SUCCESS)
			DO_ERROR(DNS_R_FORMERR);


		rdatalist = newrdatalist(msg);
		if (rdatalist == NULL) {
			result = ISC_R_NOMEMORY;
			goto cleanup;
		}
		rdataset =  isc_mempool_get(msg->rdspool);
		if (rdataset == NULL) {
			result = ISC_R_NOMEMORY;
			goto cleanup;
		}


		rdatalist->type = rdtype;
		rdatalist->rdclass = rdclass;

		dns_rdataset_init(rdataset);
		result = dns_rdatalist_tordataset(rdatalist, rdataset);
		if (result != ISC_R_SUCCESS)
			goto cleanup;

		rdataset->attributes |= DNS_RDATASETATTR_QUESTION;

		ISC_LIST_APPEND(name->list, rdataset, link);
		rdataset = NULL;
	}

	if (seen_problem)
		return (DNS_R_RECOVERABLE);
	return (ISC_R_SUCCESS);

 cleanup:
	if (rdataset != NULL) {
		INSIST(!dns_rdataset_isassociated(rdataset));
		isc_mempool_put(msg->rdspool, rdataset);
	}
#if 0
	if (rdatalist != NULL)
		isc_mempool_put(msg->rdlpool, rdatalist);
#endif
	if (free_name)
		isc_mempool_put(msg->namepool, name);

	return (result);
}
