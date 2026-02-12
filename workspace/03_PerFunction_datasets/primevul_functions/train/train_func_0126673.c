acl_verify_csa(const uschar *domain)
{
tree_node *t;
const uschar *found;
int priority, weight, port;
dns_answer dnsa;
dns_scan dnss;
dns_record *rr;
int rc, type;
uschar target[256];


while (isspace(*domain) && *domain != '\0') ++domain;
if (*domain == '\0') domain = sender_helo_name;
if (domain == NULL) domain = sender_host_address;
if (sender_host_address == NULL) return CSA_UNKNOWN;


if (domain[0] == '[')
  {
  const uschar *start = Ustrchr(domain, ':');
  if (start == NULL) start = domain;
  domain = string_copyn(start + 1, Ustrlen(start) - 2);
  }


if (string_is_ip_address(domain, NULL) != 0)
  {
  if (!dns_csa_use_reverse) return CSA_UNKNOWN;
  dns_build_reverse(domain, target);
  domain = target;
  }


t = tree_search(csa_cache, domain);
if (t != NULL) return t->data.val;

t = store_get_perm(sizeof(tree_node) + Ustrlen(domain));
Ustrcpy(t->name, domain);
(void)tree_insertnode(&csa_cache, t);


found = domain;
switch (dns_special_lookup(&dnsa, domain, T_CSA, &found))
  {


  default:
  return t->data.val = CSA_DEFER_SRV;


  case DNS_NOMATCH:
  case DNS_NODATA:
  return t->data.val = CSA_UNKNOWN;


  case DNS_SUCCEED:
  break;
  }


for (rr = dns_next_rr(&dnsa, &dnss, RESET_ANSWERS);
     rr;
     rr = dns_next_rr(&dnsa, &dnss, RESET_NEXT)) if (rr->type == T_SRV)
  {
  const uschar * p = rr->data;


  GETSHORT(priority, p);
  GETSHORT(weight, p);
  GETSHORT(port, p);

  DEBUG(D_acl)
    debug_printf_indent("CSA priority=%d weight=%d port=%d\n", priority, weight, port);


  if (priority != 1) continue;


  if (Ustrcmp(found, domain) != 0)
    return t->data.val = port & 1 ? CSA_FAIL_EXPLICIT : CSA_UNKNOWN;


  if (weight < 2) return t->data.val = CSA_FAIL_DOMAIN;

  if (weight > 2) continue;


  (void)dn_expand(dnsa.answer, dnsa.answer + dnsa.answerlen, p,
    (DN_EXPAND_ARG4_TYPE)target, sizeof(target));

  DEBUG(D_acl) debug_printf_indent("CSA target is %s\n", target);

  break;
  }


if (rr == NULL) return t->data.val = CSA_UNKNOWN;


if (Ustrcmp(target, "") == 0) return t->data.val = CSA_FAIL_NOADDR;


rc = acl_verify_csa_address(&dnsa, &dnss, RESET_ADDITIONAL, target);
if (rc != CSA_FAIL_NOADDR) return t->data.val = rc;


#if HAVE_IPV6
if (Ustrchr(sender_host_address, ':') != NULL)
  type = T_AAAA;
else
#endif
  type = T_A;


lookup_dnssec_authenticated = NULL;
switch (dns_lookup(&dnsa, target, type, NULL))
  {


  default:
    return t->data.val = CSA_DEFER_ADDR;


  case DNS_SUCCEED:
    rc = acl_verify_csa_address(&dnsa, &dnss, RESET_ANSWERS, target);
    if (rc != CSA_FAIL_NOADDR) return t->data.val = rc;


  case DNS_NOMATCH:
  case DNS_NODATA:
    return t->data.val = CSA_FAIL_NOADDR;
  }
}
