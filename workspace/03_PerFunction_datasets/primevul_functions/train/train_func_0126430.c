deliver_set_expansions(address_item *addr)
{
if (!addr)
  {
  const uschar ***p = address_expansions;
  while (*p) **p++ = NULL;
  return;
  }


if (!addr->host_list)
  {
  deliver_host = deliver_host_address = US"";
  deliver_host_port = 0;
  }
else
  {
  deliver_host = addr->host_list->name;
  deliver_host_address = addr->host_list->address;
  deliver_host_port = addr->host_list->port;
  }

deliver_recipients = addr;
deliver_address_data = addr->prop.address_data;
deliver_domain_data = addr->prop.domain_data;
deliver_localpart_data = addr->prop.localpart_data;


deliver_domain = addr->domain;
self_hostname = addr->self_hostname;

#ifdef EXPERIMENTAL_BRIGHTMAIL
bmi_deliver = 1;
bmi_alt_location = NULL;
bmi_base64_verdict = NULL;
bmi_base64_tracker_verdict = NULL;
#endif


if (!addr->next)
  {
  address_item *addr_orig;

  deliver_localpart = addr->local_part;
  deliver_localpart_prefix = addr->prefix;
  deliver_localpart_suffix = addr->suffix;

  for (addr_orig = addr; addr_orig->parent; addr_orig = addr_orig->parent) ;
  deliver_domain_orig = addr_orig->domain;


  deliver_localpart_orig = !addr_orig->router
    ? addr_orig->local_part
    : addr_orig->router->caseful_local_part
    ? addr_orig->cc_local_part
    : addr_orig->lc_local_part;


  if (addr->parent)
    {
    deliver_domain_parent = addr->parent->domain;
    deliver_localpart_parent = !addr->parent->router
      ? addr->parent->local_part
      : addr->parent->router->caseful_local_part
      ? addr->parent->cc_local_part
      : addr->parent->lc_local_part;


    if (testflag(addr, af_pfr))
      {
      if (testflag(addr, af_file))	    address_file = addr->local_part;
      else if (deliver_localpart[0] == '|') address_pipe = addr->local_part;
      deliver_localpart = addr->parent->local_part;
      deliver_localpart_prefix = addr->parent->prefix;
      deliver_localpart_suffix = addr->parent->suffix;
      }
    }

#ifdef EXPERIMENTAL_BRIGHTMAIL

    bmi_base64_verdict = bmi_get_base64_verdict(deliver_localpart_orig, deliver_domain_orig);
    bmi_base64_tracker_verdict = bmi_get_base64_tracker_verdict(bmi_base64_verdict);

    bmi_deliver = bmi_get_delivery_status(bmi_base64_verdict);

    if (bmi_deliver == 1)
      bmi_alt_location = bmi_get_alt_location(bmi_base64_verdict);
#endif

  }


else
  {
  address_item *addr2;
  if (testflag(addr, af_pfr))
    {
    if (testflag(addr, af_file))	 address_file = addr->local_part;
    else if (addr->local_part[0] == '|') address_pipe = addr->local_part;
    }
  for (addr2 = addr->next; addr2; addr2 = addr2->next)
    {
    if (deliver_domain && Ustrcmp(deliver_domain, addr2->domain) != 0)
      deliver_domain = NULL;
    if (  self_hostname
       && (  !addr2->self_hostname
          || Ustrcmp(self_hostname, addr2->self_hostname) != 0
       )  )
      self_hostname = NULL;
    if (!deliver_domain && !self_hostname) break;
    }
  }
}
