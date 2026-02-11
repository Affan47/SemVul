create_fetch(dns_validator_t *val, dns_name_t *name, dns_rdatatype_t type,
	     isc_taskaction_t callback, const char *caller)
{
	unsigned int fopts = 0;

	if (dns_rdataset_isassociated(&val->frdataset))
		dns_rdataset_disassociate(&val->frdataset);
	if (dns_rdataset_isassociated(&val->fsigrdataset))
		dns_rdataset_disassociate(&val->fsigrdataset);

	if (check_deadlock(val, name, type, NULL, NULL)) {
		validator_log(val, ISC_LOG_DEBUG(3),
			      "deadlock found (create_fetch)");
		return (DNS_R_NOVALIDSIG);
	}

	if ((val->options & DNS_VALIDATOR_NOCDFLAG) != 0)
		fopts |= DNS_FETCHOPT_NOCDFLAG;

	if ((val->options & DNS_VALIDATOR_NONTA) != 0)
		fopts |= DNS_FETCHOPT_NONTA;

	validator_logcreate(val, name, type, caller, "fetch");
	return (dns_resolver_createfetch(val->view->resolver, name, type,
					 NULL, NULL, NULL, fopts,
					 val->event->ev_sender,
					 callback, val,
					 &val->frdataset,
					 &val->fsigrdataset,
					 &val->fetch));
}
