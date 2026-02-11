qmail_lookup_cvm(struct qmail_user* user,
		     str* domain,
		     str* username,
		     str* ext)
{
  static str prefix;
  static str fullname;

  if (cvm_module_credentials[CVM_CRED_DOMAIN].len == 0)
    if (!str_copys(&cvm_module_credentials[CVM_CRED_DOMAIN],
		   qmail_envnoathost))
      return CVME_IO;

  if (qmail_users_reinit() != 0
      || qmail_domains_reinit() != 0)
    return -1;

  switch (qmail_domains_lookup(&cvm_module_credentials[CVM_CRED_DOMAIN],
			       domain, &prefix)) {
  case -1:
    return -1;
  case 0:
    if (missingdomain == 0)
      return 1;
    if (!str_copys(domain, missingdomain)
	|| !str_copys(&fullname, missinguser))
      return -1;
    break;
  default:
    fullname.len = 0;
    if (prefix.len > 0)
      if (!str_copy(&fullname, &prefix)
	  || !str_catc(&fullname, '-'))
	return -1;
    if (!str_cat(&fullname, &cvm_module_credentials[CVM_CRED_ACCOUNT]))
      return -1;
  }

  switch (qmail_users_lookup_split(user, fullname.s, username, ext)) {
  case -1:
    return -1;
  case 0:
    return 2;
  }
  return 0;
}
