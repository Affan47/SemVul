dns_message_findname(dns_message_t *msg, dns_section_t section,
		     dns_name_t *target, dns_rdatatype_t type,
		     dns_rdatatype_t covers, dns_name_t **name,
		     dns_rdataset_t **rdataset)
{
	dns_name_t *foundname;
	isc_result_t result;


	REQUIRE(msg != NULL);
	REQUIRE(VALID_SECTION(section));
	REQUIRE(target != NULL);
	REQUIRE(name == NULL || *name == NULL);

	if (type == dns_rdatatype_any) {
		REQUIRE(rdataset == NULL);
	} else {
		REQUIRE(rdataset == NULL || *rdataset == NULL);
	}

	result = findname(&foundname, target,
			  &msg->sections[section]);

	if (result == ISC_R_NOTFOUND)
		return (DNS_R_NXDOMAIN);
	else if (result != ISC_R_SUCCESS)
		return (result);

	if (name != NULL)
		*name = foundname;


	if (ISC_UNLIKELY(type == dns_rdatatype_any))
		return (ISC_R_SUCCESS);

	result = dns_message_findtype(foundname, type, covers, rdataset);
	if (result == ISC_R_NOTFOUND)
		return (DNS_R_NXRRSET);

	return (result);
}
