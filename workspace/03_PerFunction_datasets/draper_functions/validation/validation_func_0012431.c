configure_rpz_name(dns_view_t *view, const cfg_obj_t *obj, dns_name_t *name,
		   const char *str, const char *msg)
{
	isc_result_t result;

	result = dns_name_fromstring(name, str, DNS_NAME_DOWNCASE, view->mctx);
	if (result != ISC_R_SUCCESS)
		cfg_obj_log(obj, ns_g_lctx, DNS_RPZ_ERROR_LEVEL,
			    "invalid %s '%s'", msg, str);
	return (result);
}
