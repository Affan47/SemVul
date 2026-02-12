acl_verify_csa_address(dns_answer *dnsa, dns_scan *dnss, int reset,
                       uschar *target)
{
dns_record *rr;
dns_address *da;

BOOL target_found = FALSE;

for (rr = dns_next_rr(dnsa, dnss, reset);
     rr != NULL;
     rr = dns_next_rr(dnsa, dnss, RESET_NEXT))
  {


  if (rr->type != T_A
    #if HAVE_IPV6
      && rr->type != T_AAAA
    #endif
  ) continue;

  if (strcmpic(target, rr->name) != 0) continue;

  target_found = TRUE;


  for (da = dns_address_from_rr(dnsa, rr); da != NULL; da = da->next)
    {


    DEBUG(D_acl) debug_printf_indent("CSA target address is %s\n", da->address);

    if (strcmpic(sender_host_address, da->address) == 0) return CSA_OK;
    }
  }


if (target_found) return CSA_FAIL_MISMATCH;
else return CSA_FAIL_NOADDR;
}
