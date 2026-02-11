has_no_policy_mapping(linked_list_t *chain, int len)
{
	enumerator_t *enumerator, *mappings;
	x509_policy_mapping_t *mapping;
	certificate_t *cert;
	x509_t *x509;
	bool valid = TRUE;

	enumerator = chain->create_enumerator(chain);
	while (len-- > 0 && enumerator->enumerate(enumerator, &x509))
	{
		mappings = x509->create_policy_mapping_enumerator(x509);
		valid = !mappings->enumerate(mappings, &mapping);
		mappings->destroy(mappings);
		if (!valid)
		{
			cert = (certificate_t*)x509;
			DBG1(DBG_CFG, "found policyMapping in certificate '%Y', but "
				 "inhibitPolicyMapping in effect", cert->get_subject(cert));
			break;
		}
	}
	enumerator->destroy(enumerator);
	return valid;
}
