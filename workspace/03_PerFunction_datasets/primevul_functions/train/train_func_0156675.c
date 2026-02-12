tlsa_lookup(const host_item * host, dns_answer * dnsa, BOOL dane_required)
{
uschar buffer[300];
const uschar * fullname = buffer;
int rc;
BOOL sec;


(void)sprintf(CS buffer, "_%d._tcp.%.256s", host->port, host->name);

rc = dns_lookup_timerwrap(dnsa, buffer, T_TLSA, &fullname);
sec = dns_is_secure(dnsa);
DEBUG(D_transport)
  debug_printf("TLSA lookup ret %s %sDNSSEC\n", dns_rc_names[rc], sec ? "" : "not ");

switch (rc)
  {
  case DNS_AGAIN:
    return DEFER;

  case DNS_SUCCEED:
    if (sec)
      {
      DEBUG(D_transport)
	{
	dns_scan dnss;
	for (dns_record * rr = dns_next_rr(dnsa, &dnss, RESET_ANSWERS); rr;
	     rr = dns_next_rr(dnsa, &dnss, RESET_NEXT))
	  if (rr->type == T_TLSA && rr->size > 3)
	    {
	    uint16_t payload_length = rr->size - 3;
	    uschar s[MAX_TLSA_EXPANDED_SIZE], * sp = s, * p = US rr->data;

	    sp += sprintf(CS sp, "%d ", *p++);
	    sp += sprintf(CS sp, "%d ", *p++);
	    sp += sprintf(CS sp, "%d ", *p++);
	    while (payload_length-- > 0 && sp-s < (MAX_TLSA_EXPANDED_SIZE - 4))
	      sp += sprintf(CS sp, "%02x", *p++);

	    debug_printf(" %s\n", s);
	    }
	}
      return OK;
      }
    log_write(0, LOG_MAIN,
      "DANE error: TLSA lookup for %s not DNSSEC", host->name);


  case DNS_NODATA:
  case DNS_NOMATCH:
    return dane_required ? FAIL : FAIL_FORCED;

  default:
  case DNS_FAIL:
    return dane_required ? FAIL : DEFER;
  }
}
